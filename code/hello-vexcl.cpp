#include <iostream>
#include <vector>
#include <vexcl/vexcl.hpp>

int main() {
    vex::Context ctx( vex::Filter::GPU );
    std::cout << ctx << std::endl;

    size_t n = 1024 * 1024;
    std::vector<float> a(n, 1), b(n, 2);

    vex::vector<float> A(ctx, a);
    vex::vector<float> B(ctx, b);

    B += A;

    vex::copy(B, b);
    std::cout << b[42] << std::endl;
}
