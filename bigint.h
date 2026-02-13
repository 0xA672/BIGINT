#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <boost/multiprecision/cpp_int.hpp>

#if __has_include(<gmp.h>)
#include <boost/multiprecision/gmp.hpp>
#define BIGINT_HAS_GMP 1
#endif

namespace bigint {
#ifdef BIGINT_HAS_GMP
    using integer = boost::multiprecision::mpz_int;
#else
    using integer = boost::multiprecision::cpp_int;
#endif
}

using BigInt = bigint::integer;

#endif