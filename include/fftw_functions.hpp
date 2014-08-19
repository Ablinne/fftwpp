
#ifndef FFTW_FUNCTIONS_HPP
#define FFTW_FUNCTIONS_HPP

#include "fftw_config.hpp"

#define COMMA ,

#define APPLY_TO_FFTW_API(X,P)            \
X(P, execute)                             \
X(P, plan_dft)                            \
X(P, plan_dft_1d)                         \
X(P, plan_dft_2d)                         \
X(P, plan_dft_3d)                         \
X(P, plan_many_dft)                       \
X(P, plan_guru_dft)                       \
X(P, plan_guru_split_dft)                 \
X(P, plan_guru64_dft)                     \
X(P, plan_guru64_split_dft)               \
X(P, execute_dft)                         \
X(P, execute_split_dft)                   \
X(P, plan_many_dft_r2c)                   \
X(P, plan_dft_r2c)                        \
X(P, plan_dft_r2c_1d)                     \
X(P, plan_dft_r2c_2d)                     \
X(P, plan_dft_r2c_3d)                     \
X(P, plan_many_dft_c2r)                   \
X(P, plan_dft_c2r)                        \
X(P, plan_dft_c2r_1d)                     \
X(P, plan_dft_c2r_2d)                     \
X(P, plan_dft_c2r_3d)                     \
X(P, plan_guru_dft_r2c)                   \
X(P, plan_guru_dft_c2r)                   \
X(P, plan_guru_split_dft_r2c)             \
X(P, plan_guru_split_dft_c2r)             \
X(P, plan_guru64_dft_r2c)                 \
X(P, plan_guru64_dft_c2r)                 \
X(P, plan_guru64_split_dft_r2c)           \
X(P, plan_guru64_split_dft_c2r)           \
X(P, execute_dft_r2c)                     \
X(P, execute_dft_c2r)                     \
X(P, execute_split_dft_r2c)               \
X(P, execute_split_dft_c2r)               \
X(P, plan_many_r2r)                       \
X(P, plan_r2r)                            \
X(P, plan_r2r_1d)                         \
X(P, plan_r2r_2d)                         \
X(P, plan_r2r_3d)                         \
X(P, plan_guru_r2r)                       \
X(P, plan_guru64_r2r)                     \
X(P, execute_r2r)                         \
X(P, destroy_plan)                        \
X(P, forget_wisdom)                       \
X(P, cleanup)                             \
X(P, set_timelimit)                       \
X(P, plan_with_nthreads)                  \
X(P, init_threads)                        \
X(P, cleanup_threads)                     \
X(P, export_wisdom_to_filename)           \
X(P, export_wisdom_to_file)               \
X(P, export_wisdom_to_string)             \
X(P, export_wisdom)                       \
X(P, import_system_wisdom)                \
X(P, import_wisdom_from_filename)         \
X(P, import_wisdom_from_file)             \
X(P, import_wisdom_from_string)           \
X(P, import_wisdom)                       \
X(P, fprint_plan)                         \
X(P, print_plan)                          \
X(P, sprint_plan)                         \
X(P, malloc)                              \
X(P, alloc_real)                          \
X(P, alloc_complex)                       \
X(P, free)                                \
X(P, flops)                               \
X(P, estimate_cost)                       \
X(P, cost)                                \
X(P, alignment_of)


#define DECL_FFTW_FUNCTION(type, name) static decltype(type##_##name)& name;

#define DECL_FFTW_FUNCTIONS(type) APPLY_TO_FFTW_API(DECL_FFTW_FUNCTION, type)

#define DECL_FFTW_TYPE(type, name) typedef type##_##name name;

#define DECL_FFTW_STRUCT_REAL(dtype, type, real)      \
template<>                                            \
struct fftw_functions<dtype>                          \
{                                                     \
    DECL_FFTW_TYPE(type, plan)                        \
    DECL_FFTW_TYPE(type, complex)                     \
    DECL_FFTW_TYPE(type, iodim)                       \
    DECL_FFTW_TYPE(type, iodim64)                     \
    DECL_FFTW_TYPE(type, r2r_kind)                    \
    DECL_FFTW_TYPE(type, write_char_func)             \
    DECL_FFTW_TYPE(type, read_char_func)              \
                                                      \
    typedef real real_type;                           \
    static const char *version;                       \
    static const char *cc;                            \
    static const char *codelet_optim;                 \
                                                      \
    DECL_FFTW_FUNCTIONS(type)                         \
};

#define DECL_FFTW_STRUCT(dtype, type) DECL_FFTW_STRUCT_REAL(dtype, type, dtype)

#define ASSIGN_FFTW_FUNCTION(dtype,type,name) decltype(type ## _ ## name)&  fftw_functions<dtype>::name = type ## _ ## name;

#define ASSIGN_FFTW_FUNCTIONS(dtype, type)                               \
APPLY_TO_FFTW_API(ASSIGN_FFTW_FUNCTION, dtype COMMA type)                \
                                                                         \
const char *fftw_functions<dtype>::version = type##_version;             \
const char *fftw_functions<dtype>::cc = type##_cc;                       \
const char *fftw_functions<dtype>::codelet_optim = type##_codelet_optim;

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
