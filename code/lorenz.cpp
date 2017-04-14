#include <iostream>
#include <vector>
#include <vexcl/vexcl.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/vexcl/vexcl.hpp>

namespace odeint = boost::numeric::odeint;

typedef vex::multivector<double, 3> state_type;

typedef odeint::runge_kutta4_classic<
    state_type, double, state_type, double,
    odeint::vector_space_algebra, odeint::default_operations
    > Stepper;

struct lorenz_system {
    const vex::vector<double> &R;
    double sigma, b;

    void operator()(const state_type &x, state_type &dxdt, double t) const {
	dxdt = std::make_tuple(
		sigma * (x(1) - x(0)),
		R * x(0) - x(1) - x(0) * x(2),
		x(0) * x(1) - b * x(2));
    }
};

int main(int argc, char *argv[]) {
    const size_t n = (argc > 1) ? std::stoi(argv[1]) : 32;
    const double tmax = 1.0, dt = 0.01;
    const double Rmin = 0.1, Rmax = 50.0, dR = (Rmax - Rmin) / (n - 1);

    vex::Context ctx(vex::Filter::Env && vex::Filter::DoublePrecision);

    state_type X(ctx, n);
    vex::vector<double> R(ctx, n);

    X = 10.0;
    R = Rmin + dR * vex::element_index();

    lorenz_system sys{R, 10.0, 8.0/3};
    odeint::integrate_const(Stepper(), sys, X, 0.0, tmax, dt);

    std::cout << "x = " << X << std::endl;
}
