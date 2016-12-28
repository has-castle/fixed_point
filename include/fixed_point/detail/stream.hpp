#ifndef _HAS_CASTLE__FIXED_POINT__STREAM_H
#define _HAS_CASTLE__FIXED_POINT__STREAM_H

#include <iostream>
#include <string>
#include "base.hpp"

namespace has_castle
{
namespace fixed_point
{

struct format_exception : public std::invalid_argument
{
    explicit format_exception(const std::string &what_arg)
        : std::invalid_argument(what_arg) {}
    explicit format_exception(const char *what_arg)
        : std::invalid_argument(what_arg) {}
};

template <int F, typename T, typename Rhs = fixed_point<F, T>>
inline std::ostream &operator<<(std::ostream &os, const fixed_point<F, T> &rhs)
{
    os << rhs.int_part() << "+" << rhs.frac_part()
       << "/2^" << Rhs::frac_bits;
    return os;
}

template <int F, typename T, typename Rhs = fixed_point<F, T>>
inline std::istream &operator>>(std::istream &is, Rhs &rhs)
{
    typename Rhs::value_type int_part;
    typename Rhs::value_type frac_part;
    int frac_bits;
    std::string s{3, '\0'};
    is >> int_part;
    is.get(&s[0], 1);
    if (s != "+")
        throw format_exception{"Missing '+'"};
    is >> frac_part;
    is.get(&s[0], 3);
    if (s != "/2^")
        throw format_exception{"Missing '/2^'"};
    is >> frac_part;
    if (frac_part != Rhs::frac_bits)
        throw format_exception{"Unexpected exponent"};
    rhs.raw_value() = (int_part << frac_bits) | frac_part;
    return is;
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__STREAM_H