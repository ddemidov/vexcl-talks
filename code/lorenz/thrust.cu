#include <iostream>
#include <cmath>
#include <utility>
#include <cstdlib>

#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>

#include <boost/numeric/odeint.hpp>

#include <boost/numeric/odeint/external/thrust/thrust_algebra.hpp>
#include <boost/numeric/odeint/external/thrust/thrust_operations.hpp>
#include <boost/numeric/odeint/external/thrust/thrust_resize.hpp>

namespace odeint = boost::numeric::odeint;

typedef thrust::device_vector< double > state_type;

const double sigma = 10.0;
const double b     = 8.0 / 3.0;

struct lorenz_system {
    struct lorenz_functor {
        template<class T>
        __host__ __device__ void operator()( T t ) const {
            double x = thrust::get<0>(t);
            double y = thrust::get<1>(t);
            double z = thrust::get<2>(t);
            double r = thrust::get<3>(t);

            thrust::get<4>(t) = sigma * (y - x);
            thrust::get<5>(t) = r * x - y - x * z;
            thrust::get<6>(t) = -b * z + x * y ;
        }
    };

    lorenz_system(size_t N, const state_type &R) : N(N), R(R) { }

    template<class State, class Deriv>
    void operator()(const State &x, Deriv &dxdt, double t) const {
        thrust::for_each(
                thrust::make_zip_iterator( thrust::make_tuple(
                        boost::begin(x),
                        boost::begin(x) + N,
                        boost::begin(x) + 2 * N,
                        boost::begin(R),
                        boost::begin(dxdt),
                        boost::begin(dxdt) + N,
                        boost::begin(dxdt) + 2 * N ) ),
                thrust::make_zip_iterator( thrust::make_tuple(
                        boost::begin(x) + N,
                        boost::begin(x) + 2 * N,
                        boost::begin(x) + 3 * N,
                        boost::begin(R),
                        boost::begin(dxdt) + N,
                        boost::begin(dxdt) + 2 * N,
                        boost::begin(dxdt) + 3 * N ) ),
                lorenz_functor() );
    }

    size_t N;
    const  state_type &R;
};


const double dt = 0.01;
const double t_max = 100.0;

int main( int argc , char* argv[] ) {
    const size_t n = argc > 1 ? atoi(argv[1]) : 1024;

    std::vector<double> r(n);
    double Rmin = 0.1, Rmax = 50.0, dR = (Rmax - Rmin) / double(n - 1);
    for(size_t i = 0 ; i < n ; ++i)
        r[i] = Rmin + i * (Rmax - Rmin) / (n - 1);

    state_type R = r;
    state_type X(3 * n);

    thrust::fill(x.begin(), x.end(), 10.0);


    odeint::runge_kutta4<
            state_type, double, state_type, double,
            thrust_algebra , thrust_operations
            > stepper;


    lorenz_system sys(n, R);

    ctx.finish();
    vex::stopwatch<> watch;
    odeint::integrate_const(stepper, std::ref(sys), X, 0.0, t_max, dt);
    ctx.finish();
    double time = watch.toc();

    std::cout << "t = " << time << std::endl;

    cout << X[0] << endl;



    return 0;
}
