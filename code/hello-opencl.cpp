#include <iostream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

int main() {
    // Get list of OpenCL platforms.
    std::vector<cl::Platform> platform;
    cl::Platform::get(&platform);

    if (platform.empty())
        throw std::runtime_error("No OpenCL platforms");

    // Get first available GPU.
    cl::Context context;
    std::vector<cl::Device> device;
    for(auto p = platform.begin(); device.empty() && p != platform.end(); p++) {
        std::vector<cl::Device> pldev;
        try {
            p->getDevices(CL_DEVICE_TYPE_GPU, &pldev);
            for(auto d = pldev.begin(); device.empty() && d != pldev.end(); d++) {
                if (!d->getInfo<CL_DEVICE_AVAILABLE>()) continue;
                device.push_back(*d);
                context = cl::Context(device);
            }
        } catch(...) {
            device.clear();
        }
    }
    if (device.empty()) throw std::runtime_error("No GPUs");

    // Create command queue.
    cl::CommandQueue queue(context, device[0]);

    // Prepare input data, transfer it to the device.
    const size_t N = 1 << 20;
    std::vector<float> a(N, 1), b(N, 2), c(N);

    cl::Buffer A(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
            a.size() * sizeof(float), a.data());

    cl::Buffer B(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
            b.size() * sizeof(float), b.data());

    cl::Buffer C(context, CL_MEM_READ_WRITE,
            c.size() * sizeof(float));

    // Create kernel source
    const char source[] = R"(
        kernel void add(
          ulong n,
          global const float *a,
          global const float *b,
          global float *c
          )
        {
          ulong i = get_global_size(0);
          if (i < n) c[i] = a[i] + b[i];
        }
        )";

    // Compile OpenCL program for the device.
    cl::Program program(context, cl::Program::Sources(
                1, std::make_pair(source, strlen(source))
                ));
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

    // Set kernel parameters.
    add.setArg(0, static_cast<cl_ulong>(N));
    add.setArg(1, A);
    add.setArg(2, B);
    add.setArg(3, C);

    // Launch kernel on the compute device.
    queue.enqueueNDRangeKernel(add, cl::NullRange, N, cl::NullRange);

    // Get result back to host.
    queue.enqueueReadBuffer(C, CL_TRUE, 0, c.size() * sizeof(float), c.data());
    std::cout << c[42] << std::endl; // Should get '3' here.
}
