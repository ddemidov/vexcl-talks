#include <iostream>
#include <vector>
#include <vexcl/vexcl.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/external/vexcl/vexcl.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace odeint = boost::numeric::odeint;
namespace py = pybind11;

typedef vex::multivector<double, 3> state_type;

typedef odeint::runge_kutta4_classic<
    state_type, double, state_type, double,
    odeint::vector_space_algebra, odeint::default_operations
    > Stepper;

vex::Context& ctx(std::string name = "") {
    static vex::Context c(vex::Filter::Env && vex::Filter::Name(name));
    return c;
}

struct lorenz_system {
    int n;
    double sigma, b;
    vex::vector<double> R;
    state_type X;

    lorenz_system(double sigma, double b, py::array_t<double> R)
        : n(R.size()), sigma(sigma), b(b), R(ctx(), n, R.data()), X(ctx(), n) {}

    void operator()(const state_type &x, state_type &dxdt, double t) const {
	dxdt = std::make_tuple(
		sigma * (x(1) - x(0)),
		R * x(0) - x(1) - x(0) * x(2),
		x(0) * x(1) - b * x(2));
    }

    py::array_t<double> advance(py::array_t<double> x_in, int steps, double dt) {
        for(int i=0, b=0, e=n; i<3; ++i, b+=n, e+=n)
            vex::copy(x_in.data()+b, x_in.data()+e, X(i).begin());

        odeint::integrate_n_steps(Stepper(), std::ref(*this), X, 0.0, dt, steps);

        py::array_t<double> x_out(std::array<size_t,2>{x_in.shape(0), x_in.shape(1)});
        for(int i=0, b=0; i<3; ++i, b+=n)
            vex::copy(X(i).begin(), X(i).end(), x_out.mutable_data()+b);

        return x_out;
    }
};

PYBIND11_PLUGIN(pylorenz) {
    py::module m("pylorenz");

    m.def("context", [](std::string name) {
            std::ostringstream s; s << ctx(name); py::print(s.str());
            }, py::arg("name") = std::string(""));

    py::class_<lorenz_system>(m, "Stepper")
        .def(py::init<double, double, py::array_t<double>>())
        .def("advance", &lorenz_system::advance)
        ;

    return m.ptr();
}
