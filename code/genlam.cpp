#include <iostream>
#include <vexcl/vexcl.hpp>

struct power {
    double E;

    power(double E) : E(E) {}

    template <class Expr>
    auto operator()(const Expr &expr) const -> decltype( pow(expr, E) ) {
        return pow(expr, E);
    }
};

void before(const vex::vector<double> &x, vex::vector<double> &y) {
    power pow2(2);

    y = pow2( sin(x) );
}

void after(const vex::vector<double> &x, vex::vector<double> &y) {
    auto pow2 = [E=2.0](const auto &expr) { return pow(expr, E); };

    y = pow2( sin(x) );
}

int main() {
    vex::Context ctx(vex::Filter::Env);
    vex::vector<double> x(ctx, 16);
    vex::vector<double> y(ctx, 16);

    x = 1;
    before(x, y);
    std::cout << y << std::endl;

    x = 1;
    after(x, y);
    std::cout << y << std::endl;
}
