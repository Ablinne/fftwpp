
#include "fftw_functions.hpp"

namespace fftw
{
    int init_threads()
    {
        int s = 1;
        s = s && fftw_init_threads();
        s = s && fftwf_init_threads();
        s = s && fftwl_init_threads();
#   ifdef FFTWQ_REAL
        s = s && fftwq_init_threads();
#   endif //FFTWQ_REAL

#if defined(_OPENMP)
        fftw_plan_with_nthreads(omp_get_max_threads())
        fftwf_plan_with_nthreads(omp_get_max_threads())
        fftwl_plan_with_nthreads(omp_get_max_threads())
#   ifdef FFTWQ_REAL
        fftwq_plan_with_nthreads(omp_get_max_threads())
#   endif //FFTWQ_REAL
#endif // _OPENMP
        return s;
    }

    void cleanup_threads()
    {
        fftw_cleanup_threads();
        fftwf_cleanup_threads();
        fftwl_cleanup_threads();
#   ifdef FFTWQ_REAL
        fftwq_cleanup_threads();
#   endif //FFTWQ_REAL
    }

    ASSIGN_FFTW_FUNCTIONS(float, fftwf)
    ASSIGN_FFTW_FUNCTIONS(double, fftw)
    ASSIGN_FFTW_FUNCTIONS(long double, fftwl)

#ifdef FFTWQ_REAL
    ASSIGN_FFTW_FUNCTIONS(__float128, fftwq)
    ASSIGN_FFTW_FUNCTIONS(boost::multiprecision::float128, fftwq)
#endif //FFTWQ_REAL
}
