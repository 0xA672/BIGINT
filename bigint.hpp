#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <boost/multiprecision/cpp_int.hpp>
#if __has_include(<gmp.h>)
#include <boost/multiprecision/gmp.hpp>
#endif

#include <optional>
#include <string>
#include <ostream>
#include <cstddef>
#include <algorithm>

namespace bigint_ns {

#ifdef BIGINT_HAS_GMP
    using backend = boost::multiprecision::mpz_int;
#else
    using backend = boost::multiprecision::cpp_int;
#endif

    using BigInt = backend;

    inline namespace literals {
        BigInt operator""_bi(const char* str, std::size_t) {
            return BigInt(str);
        }
    }

    inline std::optional<BigInt> from_string(const std::string& s) noexcept {
        try { return BigInt(s); }
        catch (...) { return std::nullopt; }
    }

    template <typename CharT>
    std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const BigInt& num) {
        std::string s = num.str();
        if ((os.flags() & std::ios_base::showbase) || s.empty())
            return os << s;
        std::string result;
        if (s[0] == '-') {
            result += '-';
        }
        int cnt = 0;
        for (auto it = s.rbegin(); it != s.rend() && *it != '-'; ++it) {
            result.push_back(*it);
            ++cnt;
            if (cnt % 3 == 0 && it + 1 != s.rend() && *(it + 1) != '-')
                result.push_back(',');
        }
        std::reverse(result.begin() + (s[0]=='-'?1:0), result.end());
        return os << result;
    }

}

using BigInt = bigint_ns::BigInt;

#endif
