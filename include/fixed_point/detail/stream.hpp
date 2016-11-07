#ifndef _HAS_CASTLE__FIXED_POINT__STREAM_H
#define _HAS_CASTLE__FIXED_POINT__STREAM_H

#include <iostream>
#include "base.hpp"

namespace has_castle
{
namespace fixed_point
{

template <int F, typename T>
inline std::ostream &operator<<(std::ostream &os, fixed_point<F, T> fp)
{
    os << fp.int_part() << "+" << fp.frac_part()
       << "/2^" << decltype(fp)::frac_bits::value;
    return os;
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__STREAM_H