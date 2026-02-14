#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <boost/multiprecision/cpp_int.hpp>
#if __has_include(<gmp.h>)
#define BIGINT_HAS_GMP
#include <boost/multiprecision/gmp.hpp>
#endif

#include <optional>
#include <string>
#include <ostream>
#include <locale>
#include <cstddef>
#include <ios>

namespace bigint_ns {

#ifdef BIGINT_HAS_GMP
    using backend = boost::multiprecision::mpz_int;
#else
    using backend = boost::multiprecision::cpp_int;
#endif

    using BigInt = backend;

    inline namespace literals {
        [[nodiscard]] BigInt operator""_bi(const char* str, std::size_t) {
            return BigInt(str);
        }
    }

    [[nodiscard]] inline std::optional<BigInt> from_string(const std::string& s) noexcept {
        if (s.empty()) return std::nullopt;
        try { return BigInt(s); }
        catch (...) { return std::nullopt; }
    }

    template <typename CharT>
    [[nodiscard]] std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>& os, const BigInt& num) {
        int base = 10;
        auto flags = os.flags();
        auto basefield = flags & std::ios_base::basefield;
        if (basefield == std::ios_base::oct)
            base = 8;
        else if (basefield == std::ios_base::hex)
            base = 16;

        std::string s = num.str(base);
        bool negative = !s.empty() && s[0] == '-';
        std::string abs_s = negative ? s.substr(1) : s;

        bool show_base = (flags & std::ios_base::showbase) != 0;
        bool uppercase = (flags & std::ios_base::uppercase) != 0;

        if (show_base && base != 10 && abs_s != "0") {
            if (base == 16)
                abs_s = (uppercase ? "0X" : "0x") + abs_s;
            else if (base == 8)
                abs_s = "0" + abs_s;
        }

        if (base == 16 && uppercase) {
            for (char& c : abs_s)
                if (c >= 'a' && c <= 'f')
                    c -= 'a' - 'A';
        }

        std::string result;
        if (negative) {
            result = "-";
        } else if (base == 10 && (flags & std::ios_base::showpos) && abs_s != "0") {
            result = "+";
        }

        if (base == 10) {
            std::string digits = std::move(abs_s);
            std::size_t len = digits.size();
            if (len <= 3) {
                result += digits;
            } else {
                char thousands_sep = ',';
                std::string grouping = "\3";
                try {
                    const auto& np = std::use_facet<std::numpunct<char>>(os.getloc());
                    thousands_sep = np.thousands_sep();
                    grouping = np.grouping();
                } catch (const std::bad_cast&) {
                }

                std::string formatted;
                formatted.reserve(len + len / 3);

                if (grouping.empty() || grouping[0] == '\0') {
                    formatted = digits;
                } else {
                    std::size_t group = static_cast<unsigned char>(grouping[0]);
                    if (group == 0) group = 3;
                    std::size_t first_group = len % group;
                    std::size_t pos = 0;
                    if (first_group != 0) {
                        formatted.append(digits, 0, first_group);
                        pos = first_group;
                    }
                    while (pos < len) {
                        if (pos != 0) formatted.push_back(thousands_sep);
                        std::size_t take = group;
                        if (pos + take > len) take = len - pos;
                        formatted.append(digits, pos, take);
                        pos += take;
                    }
                }
                result += formatted;
            }
        } else {
            result += abs_s;
        }

        return os << result;
    }

}

using BigInt = bigint_ns::BigInt;

#endif
