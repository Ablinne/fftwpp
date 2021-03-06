
#ifndef FFTWPP_HPP
#define FFTWPP_HPP

#include "fftw_vector.hpp"
#include "fftw_functions.hpp"

namespace fftw
{

    template<class real_type>
    struct fftwpp: fftw_functions<real_type> {
        typedef typename vector_types<real_type>::vector vector;
        typedef typename vector_types<real_type>::cvector cvector;
        typedef typename vector_types<real_type>::uvector uvector;
        typedef typename vector_types<real_type>::ucvector ucvector;

        static typename fftw_functions<real_type>::real_type* ptr(typename vector_types<real_type>::uvector &vec)
        {
            return reinterpret_cast<typename fftw_functions<real_type>::real_type*>(vec.data().data());
        }

        static typename fftw_functions<real_type>::complex* ptr(typename vector_types<real_type>::ucvector &vec)
        {
            return reinterpret_cast<typename fftw_functions<real_type>::complex*>(vec.data().data());
        }

        static typename fftw_functions<real_type>::real_type* ptr(typename vector_types<real_type>::vector &vec)
        {
            return reinterpret_cast<typename fftw_functions<real_type>::real_type*>(vec.data());
        }

        static typename fftw_functions<real_type>::complex* ptr(typename vector_types<real_type>::cvector &vec)
        {
            return reinterpret_cast<typename fftw_functions<real_type>::complex*>(vec.data());
        }
    };

}

#endif //FFTWPP_HPP
