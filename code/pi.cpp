#include <iostream>
#include <random>
#include <chrono>
#include <vexcl/vexcl.hpp>

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char *argv[]) {
    const size_t n = argc > 1 ? std::stoi(argv[1]) : 1024 * 1024;
    const size_t seed = std::random_device()();

    vex::Context ctx(vex::Filter::Env && vex::Filter::Count(1));
    std::cout << ctx << std::endl;

    vex::Random<cl_double2> rnd;
    vex::Reductor<size_t, vex::SUM> sum(ctx);

    double pi = 4.0 * sum( length( rnd(vex::element_index(0, n), seed) ) < 1.0 ) / n;

    auto tic = Clock::now();
    pi = 4.0 * sum( length( rnd(vex::element_index(0, n), seed) ) < 1.0 ) / n;
    auto toc = Clock::now();

    std::cout << "𝛑 ≈ " << pi << std::endl;
    std::cout << Clock::duration(toc - tic).count() *
        static_cast<double>(Clock::duration::period::num) /
                    Clock::duration::period::den
                    << " s" << std::endl;
}
