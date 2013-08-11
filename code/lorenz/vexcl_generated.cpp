#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <tuple>
#include <memory>
#include <vexcl/vexcl.hpp>
#include <boost/numeric/odeint.hpp>

namespace odeint = boost::numeric::odeint;

typedef vex::symbolic< double > sym_vector;
typedef std::array<sym_vector, 3> sym_state;

const double sigma = 10.0;
const double b = 8.0 / 3.0;

struct lorenz_system
{
    const sym_vector &R;

    lorenz_system( const sym_vector &_R ) : R( _R ) {}

    void operator()( const sym_state &x , sym_state &dxdt , double t ) const
    {
	dxdt[0] = sigma * (x[1] - x[0]);
	dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
	dxdt[2] = x[0] * x[1] - b * x[2];
    }
};

size_t n;
const double dt = 0.01;
const double t_max = 100.0;

int main( int argc , char **argv ) {
    using namespace std;

    n = argc > 1 ? atoi( argv[1] ) : 1024;

    vex::Context ctx( vex::Filter::Exclusive( vex::Filter::DoublePrecision && vex::Filter::Env ) );
    //cout << ctx << endl;


    // Custom kernel body will be recorded here:
    std::ostringstream body;
    vex::generator::set_recorder(body);

    // State types that would become kernel parameters:
    sym_state  sym_S = {{
	sym_vector(sym_vector::VectorParameter),
	sym_vector(sym_vector::VectorParameter),
	sym_vector(sym_vector::VectorParameter)
    }};

    sym_vector sym_R(sym_vector::VectorParameter, sym_vector::Const);

    // Symbolic stepper:
    odeint::runge_kutta4<
	    sym_state, double, sym_state, double,
	    odeint::range_algebra, odeint::default_operations
	    > sym_stepper;

    lorenz_system sys(sym_R);
    sym_stepper.do_step(std::ref(sys), sym_S, 0, dt);

    auto kernel = vex::generator::build_kernel(
            ctx, "lorenz", body.str(),
	    sym_S[0], sym_S[1], sym_S[2], sym_R
	    );

    // Real state initialization:
    double Rmin = 0.1, Rmax = 50.0, dR = (Rmax - Rmin) / double(n - 1);

    vex::vector<double> X(ctx.queue(), n);
    vex::vector<double> Y(ctx.queue(), n);
    vex::vector<double> Z(ctx.queue(), n);
    vex::vector<double> R(ctx.queue(), n);

    vex::tie(X, Y, Z) = 10.0;
    R = Rmin + dR * vex::element_index();

    // Integration loop:
    ctx.finish();
    vex::stopwatch<> watch;
    for(double t = 0; t < t_max; t += dt)
	kernel(X, Y, Z, R);
    ctx.finish();
    double time = watch.toc();

    std::cout << n << " " << time << std::endl;

    //cout << X[0] << endl;
}
