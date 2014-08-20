
#ifndef FFTW_VECTOR_HPP
#define FFTW_VECTOR_HPP

#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include "fftw_functions.hpp"
using namespace boost::numeric;
namespace fftw
{
    template<class T>
    struct remove_complex
    {
        typedef T value_type;
    };

    template<class T>
    struct remove_complex<std::complex<T>>
    {
        typedef T value_type;
    };

    template <typename Tp>
    class allocator
    {
    public:
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Tp* pointer;
        typedef const Tp* const_pointer;
        typedef Tp& reference;
        typedef const Tp& const_reference;
        typedef Tp value_type;
        typedef fftw_functions<typename remove_complex<Tp>::value_type> FFTW;

        template<typename Tp1> struct rebind {
            typedef allocator<Tp1> other;
        };

        allocator() throw() { }
        allocator(const allocator&) throw() { }
        template<typename Tp1> allocator(const allocator<Tp1>&) throw() { }
        ~allocator() throw() { }

        pointer allocate(size_type n, const void* = 0)
        {
            return static_cast<Tp*>(FFTW::malloc(n * sizeof(Tp)));
        }

        void deallocate(pointer p, size_type)
        {
            FFTW::free(p);
        }

        size_type max_size() const
        {
            return std::numeric_limits<size_t>::max() / sizeof(Tp);
        }

        void construct(pointer p)
        {
            ::new((void *)p) Tp();
        }

        void construct(pointer p, const Tp& val)
        {
            ::new((void *)p) Tp(val);
        }

        void destroy(pointer p)
        {
            p->~Tp();
        }

        bool operator==(const allocator<Tp> &/*other*/) const
        {
            // This allocator does not carry any state, so they are all the same
            return true;
        }

        bool operator!=(const allocator<Tp> &other) const
        {
            return !(*this==other);
        }

    };

    template<typename T>
    struct vector_types
    {
        typedef std::vector< T, allocator<T> > vector;
        typedef std::vector< std::complex<T>, allocator< std::complex<T> > > cvector;
        typedef ublas::vector< T, std::vector< T, allocator<T> > > uvector;
        typedef ublas::vector< std::complex<T>, std::vector< std::complex<T>, allocator< std::complex<T> > > > ucvector;
    };

}

#endif
