#include <iostream>
#include <vector>
#include <vexcl/vexcl.hpp>

int main() {
    // Get first available GPU
    vex::Context ctx(vex::Filter::GPU && vex::Filter::Count(1));
    if (!ctx) throw std::runtime_error("No GPUs");

    // Prepare and copy input data
    const size_t n = 1024 * 1024;
    std::vector<float> a(n, 1), b(n, 2), c(n);
    vex::vector<float> A(ctx, a), B(ctx, b), C(ctx, n);

    // Launch compute kernel
    C = A + B;

    // Get results back to host
    vex::copy(C, c);
    std::cout << c[42] << std::endl;
}
