#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

int main() {
    std::vector<cl::Platform> platform;
    cl::Platform::get(&platform);

    if (platform.empty())
        throw std::runtime_error("No OpenCL platforms");

    cl::Context context;
    std::vector<cl::Device> device;
    for(auto p = platform.begin(); device.empty() && p != platform.end(); p++) {
        std::vector<cl::Device> dev;
        p->getDevices(CL_DEVICE_TYPE_GPU, &dev);
        for(auto d = dev.begin(); device.empty() && d != dev.end(); d++) {
            if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;
            device.push_back(*d);
            try {
                context = cl::Context(device);
            } catch(...) {
                device.clear();
            }
        }
    }
    if (device.empty()) throw std::runtime_error("No GPUs");

    cl::CommandQueue queue(context, device[0]);

    const size_t n = 1024 * 1024;
    std::vector<double> a(n, 1.5), b(n, 2.7);

    cl::Buffer A(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
            a.size() * sizeof(a[0]), a.data());

    cl::Buffer B(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
            b.size() * sizeof(b[0]), b.data());

    std::string source = R"(
        kernel void add(ulong n, global const double *a, global double *b) {
          ulong i = get_global_id(0);
          if (i < n) b[i] += a[i];
        }
        )";

    cl::Program program(context, source);

    try {
        program.build(device);
    } catch (const cl::Error&) {
        std::cerr
            << "OpenCL compilation error" << std::endl
            << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device[0])
            << std::endl;
        throw std::runtime_error("OpenCL build error");
    }
    cl::Kernel add(program, "add");

    add.setArg(0, static_cast<cl_ulong>(n));
    add.setArg(1, A);
    add.setArg(2, B);

    queue.enqueueNDRangeKernel(add, cl::NullRange, n, cl::NullRange);

    queue.enqueueReadBuffer(B, CL_TRUE, 0, b.size() * sizeof(b[0]), b.data());
    std::cout << b[42] << std::endl;
}
