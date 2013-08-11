#include <iostream>
#include <cmath>
#include <utility>
#include <cstdlib>

#include <thrust/device_vector.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>

#include <boost/numeric/odeint.hpp>

#include <boost/numeric/odeint/external/thrust/thrust_resize.hpp>

#include <boost/timer.hpp>

#include <cublas_v2.h>

typedef thrust::device_vector< double > state_type;

cublasHandle_t cublas_handle;

namespace boost {
namespace numeric {
namespace odeint {

/* only defined for doubles */
struct cublas_operations
{
    //template< class Fac1 , class Fac2 > struct scale_sum2;

    template< class F1 = double , class F2 = F1 >
    struct scale_sum2
    {
        typedef double Fac1;
        typedef double Fac2;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum2( const Fac1 alpha1 , const Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            if( thrust::raw_pointer_cast(&(t2[0])) != thrust::raw_pointer_cast(&(t1[0])) )
            {
                cublasDcopy(cublas_handle, n, thrust::raw_pointer_cast(&(t2[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            }

            cublasDscal(cublas_handle, n, &m_alpha1, thrust::raw_pointer_cast(&(t1[0])), 1 );
            cublasDaxpy(cublas_handle, n, &m_alpha2, thrust::raw_pointer_cast(&(t3[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1 );
        }
    };

    template< class F1 = double , class F2 = F1 , class F3 = F2 >
    struct scale_sum3
    {
        typedef double Fac1;
        typedef double Fac2;
        typedef double Fac3;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;

        scale_sum3( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) { }

        template< class T1 , class T2 , class T3 , class T4 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            if( thrust::raw_pointer_cast(&(t2[0])) != thrust::raw_pointer_cast(&(t1[0])) )
            {
                cublasDcopy(cublas_handle, n, thrust::raw_pointer_cast(&(t2[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            }
            cublasDscal(cublas_handle, n, &m_alpha1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha2, thrust::raw_pointer_cast(&(t3[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha3, thrust::raw_pointer_cast(&(t4[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
        }
    };

    template< class F1 = double , class F2 = F1 , class F3 = F2 , class F4 = F3 >
    struct scale_sum4
    {
        typedef double Fac1;
        typedef double Fac2;
        typedef double Fac3;
        typedef double Fac4;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;

        scale_sum4( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            if( thrust::raw_pointer_cast(&(t2[0])) != thrust::raw_pointer_cast(&(t1[0])) )
            {
                cublasDcopy(cublas_handle, n, thrust::raw_pointer_cast(&(t2[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            }

            cublasDscal(cublas_handle, n, &m_alpha1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha2, thrust::raw_pointer_cast(&(t3[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha3, thrust::raw_pointer_cast(&(t4[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha4, thrust::raw_pointer_cast(&(t5[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
        }
    };


    template< class F1 = double , class F2 = F1 , class F3 = F2 , class F4 = F3 , class F5 = F4 >
    struct scale_sum5
    {
        typedef double Fac1;
        typedef double Fac2;
        typedef double Fac3;
        typedef double Fac4;
        typedef double Fac5;
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;
        const Fac3 m_alpha3;
        const Fac4 m_alpha4;
        const Fac5 m_alpha5;

        scale_sum5( const Fac1 alpha1 , const Fac2 alpha2 , const Fac3 alpha3 , const Fac4 alpha4 , const Fac5 alpha5 )
            : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) , m_alpha3( alpha3 ) , m_alpha4( alpha4 ) , m_alpha5( alpha5 ) { }

        template< class T1 , class T2 , class T3 , class T4 , class T5 , class T6   >
        void operator()( T1 &t1 , const T2 &t2 , const T3 &t3 , const T4 &t4 , const T5 &t5 , const T6 &t6 ) const
        {   // t1 = m_alpha1 * t2 + m_alpha2 * t3 + m_alpha3 * t4 + m_alpha4 * t5 + m_alpha5 * t6;
            // we get Containers that have size() and [i]-access

            const int n = t1.size();
            if( thrust::raw_pointer_cast(&(t2[0])) != thrust::raw_pointer_cast(&(t1[0])) )
            {
                cublasDcopy(cublas_handle, n, thrust::raw_pointer_cast(&(t2[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            }

            cublasDscal(cublas_handle, n, &m_alpha1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha2, thrust::raw_pointer_cast(&(t3[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha3, thrust::raw_pointer_cast(&(t4[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha4, thrust::raw_pointer_cast(&(t5[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
            cublasDaxpy(cublas_handle, n, &m_alpha5, thrust::raw_pointer_cast(&(t6[0])), 1, thrust::raw_pointer_cast(&(t1[0])), 1);
        }
    };

};

} // odeint
} // numeric
} // boost

namespace odeint = boost::numeric::odeint;

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
    cublasCreate(&cublas_handle);

    const size_t n = argc > 1 ? atoi(argv[1]) : 1024;

    std::vector<double> r(n);
    double Rmin = 0.1, Rmax = 50.0, dR = (Rmax - Rmin) / double(n - 1);
    for(size_t i = 0 ; i < n ; ++i)
        r[i] = Rmin + i * dR;

    state_type R = r;
    state_type X(3 * n);

    thrust::fill(X.begin(), X.end(), 10.0);


    odeint::runge_kutta4<
            state_type, double, state_type, double,
            odeint::vector_space_algebra , odeint::cublas_operations
            > stepper;


    lorenz_system sys(n, R);


    cudaThreadSynchronize();
    boost::timer timer;
    odeint::integrate_const(stepper, boost::ref(sys), X, 0.0, t_max, dt);
    cudaThreadSynchronize();
    double time = timer.elapsed();

    std::cout << n << " " << time << std::endl;

    //std::cout << X[0] << std::endl;

    cublasDestroy(cublas_handle);
}
