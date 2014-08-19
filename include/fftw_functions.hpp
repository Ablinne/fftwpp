
#ifndef FFTW_FUNCTIONS_HPP
#define FFTW_FUNCTIONS_HPP

#include "fftw_config.hpp"

#define COMMA ,

#define APPLY_TO_FFTW_API(X,P)                        \
X(P, plan_with_nthreads)                              \
X(P, plan_many_dft_r2c)                               \
X(P, plan_many_dft_c2r)                               \
X(P, destroy_plan)                                    \
X(P, execute_dft_r2c)                                 \
X(P, execute_dft_c2r)                                 \
X(P, malloc)                                          \
X(P, free)

#define DECL_FFTW_FUNCTION(type, name) static decltype(type##_##name)& name;

#define DECL_FFTW_FUNCTIONS(type) APPLY_TO_FFTW_API(DECL_FFTW_FUNCTION, type)

#define DECL_FFTW_STRUCT_REAL(dtype, type, real)      \
template<>                                            \
struct fftw_functions<dtype>                          \
{                                                     \
    typedef type##_plan plan;                         \
    typedef type##_complex complex;                   \
    typedef real real_type;                           \
                                                      \
    DECL_FFTW_FUNCTIONS(type)                         \
};

#define DECL_FFTW_STRUCT(dtype, type) DECL_FFTW_STRUCT_REAL(dtype, type, dtype)

#define ASSIGN_FFTW_FUNCTION(dtype,type,name) decltype(type ## _ ## name)&  fftw_functions<dtype>::name = type ## _ ## name;

#define ASSIGN_FFTW_FUNCTIONS(dtype, type) APPLY_TO_FFTW_API(ASSIGN_FFTW_FUNCTION, dtype COMMA type)

namespace fftw
{

    int init_threads();
    void cleanup_threads();

    template<typename real_type>
    struct fftw_functions {};

    DECL_FFTW_STRUCT(float, fftwf)
    DECL_FFTW_STRUCT(double, fftw)
    DECL_FFTW_STRUCT(long double, fftwl)

#ifdef FFTWQ_REAL
    DECL_FFTW_STRUCT(__float128, fftwq)
    DECL_FFTW_STRUCT_REAL(boost::multiprecision::float128, fftwq, __float128)
#endif //FFTWQ_REAL

}

#endif
