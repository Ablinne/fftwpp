
#ifndef FFTW_FUNCTIONS_HPP
#define FFTW_FUNCTIONS_HPP

#include "fftw_config.hpp"

#define DECL_FFTW_FUNCTION(type, name) static decltype(type##_##name)& name;

#define DECL_FFTW_FUNCTIONS(type)                     \
DECL_FFTW_FUNCTION(type, plan_with_nthreads)          \
DECL_FFTW_FUNCTION(type, plan_many_dft_r2c)           \
DECL_FFTW_FUNCTION(type, plan_many_dft_c2r)           \
DECL_FFTW_FUNCTION(type, destroy_plan)                \
DECL_FFTW_FUNCTION(type, execute_dft_r2c)             \
DECL_FFTW_FUNCTION(type, execute_dft_c2r)             \
DECL_FFTW_FUNCTION(type, malloc)                      \
DECL_FFTW_FUNCTION(type, free)

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

#define ASSIGN_FFTW_FUNCTIONS(dtype, type)            \
ASSIGN_FFTW_FUNCTION(dtype, type, plan_with_nthreads) \
ASSIGN_FFTW_FUNCTION(dtype, type, plan_many_dft_r2c)  \
ASSIGN_FFTW_FUNCTION(dtype, type, plan_many_dft_c2r)  \
ASSIGN_FFTW_FUNCTION(dtype, type, destroy_plan)       \
ASSIGN_FFTW_FUNCTION(dtype, type, execute_dft_r2c)    \
ASSIGN_FFTW_FUNCTION(dtype, type, execute_dft_c2r)    \
ASSIGN_FFTW_FUNCTION(dtype, type, malloc)             \
ASSIGN_FFTW_FUNCTION(dtype, type, free)

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
