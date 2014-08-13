
#ifndef FFTW_CONFIG_HPP
#define FFTW_CONFIG_HPP

#include <boost/config.hpp>
#include <limits>
#include <vector>

#include <complex>
#include <fftw3.h>

#ifdef FFTWQ
# if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)) \
  && !(defined(__ICC) || defined(__INTEL_COMPILER)) \
  && (defined(__i386__) || defined(__x86_64__) || defined(__ia64__))

#define FFTWQ_REAL

# endif
#endif

#ifdef FFTWQ_REAL
#include <boost/multiprecision/float128.hpp>

static_assert(std::is_standard_layout<boost::multiprecision::float128>::value,"no standard type");
static_assert(sizeof(boost::multiprecision::float128) == sizeof(__float128),"size mismatch");
#endif


#endif //FFTW_CONFIG_HPP
