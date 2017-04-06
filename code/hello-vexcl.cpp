#include <iostream>
#include <vector>
#include <vexcl/vexcl.hpp>

int main() {
    vex::Context ctx( vex::Filter::GPU );
    if (!ctx) throw std::runtime_error("No GPUs");

    size_t n = 1024 * 1024;
    std::vector<double> a(n, 1), b(n, 2);

    vex::vector<double> A(ctx, a);
    vex::vector<double> B(ctx, b);

    B += A;

    vex::copy(B, b);
    std::cout << b[42] << std::endl;
}
