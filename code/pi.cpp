#include <iostream>
#include <random>
#include <vexcl/vexcl.hpp>

int main(int argc, char *argv[]) {
    const size_t n = argc > 1 ? std::stoi(argv[1]) : 1024 * 1024;
    const size_t seed = std::random_device()();

    vex::Context ctx(vex::Filter::Env);
    std::cout << ctx << std::endl;

    vex::Random<cl_double2> rnd;
    vex::Reductor<size_t, vex::SUM> sum(ctx);

    double pi = 4.0 * sum( length( rnd(vex::element_index(0, n), seed) ) < 1.0 ) / n;

    std::cout << "𝛑 ≈ " << pi << std::endl;
}
