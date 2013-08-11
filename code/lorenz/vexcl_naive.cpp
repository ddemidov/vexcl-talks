#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <vexcl/vexcl.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/external/vexcl/vexcl_resize.hpp>

namespace odeint = boost::numeric::odeint;

typedef vex::vector< double >        vector_type;
typedef vex::multivector< double, 3 > state_type;

const double sigma = 10.0;
const double b     = 8.0 / 3.0;

struct lorenz_system {
    const vector_type &R;

    lorenz_system( const vector_type &_R ) : R( _R ) { }

    void operator()(const state_type &x, state_type &dxdt, double t) {
        auto X = vex::tag<1>( x(0) );
        auto Y = vex::tag<2>( x(1) );
        auto Z = vex::tag<3>( x(2) );

	dxdt = std::tie(
		sigma * (Y - X),
		R * X - Y - X * Z,
		X * Y - b * Z
		);
    }
};

size_t n;
const double dt = 0.01;
const double t_max = 100.0;

int main( int argc , char **argv ) {
    n = argc > 1 ? atoi(argv[1]) : 1024;
    using namespace std;

    vex::Context ctx( vex::Filter::Exclusive( vex::Filter::DoublePrecision && vex::Filter::Env ) );
    std::cout << ctx << std::endl;

    double Rmin = 0.1, Rmax = 50.0, dR = (Rmax - Rmin) / double(n - 1);

    state_type  X(ctx.queue(), n);
    vector_type R(ctx.queue(), n);

    X = 10.0;
    R = Rmin + dR * vex::element_index();

    odeint::runge_kutta4<
	    state_type, double, state_type, double ,
	    odeint::vector_space_algebra, odeint::default_operations
	    > stepper;

    lorenz_system sys(R);

    ctx.finish();
    vex::stopwatch<> watch;
    odeint::integrate_const(stepper, std::ref(sys), X, 0.0, t_max, dt);
    ctx.finish();
    double time = watch.toc();

    std::cout << "t = " << time << std::endl;

    cout << X(0)[0] << endl;
}
