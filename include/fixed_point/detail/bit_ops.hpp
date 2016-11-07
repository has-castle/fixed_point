#ifndef _HAS_CASTLE__FIXED_POINT__BITOPS_H
#define _HAS_CASTLE__FIXED_POINT__BITOPS_H

#include "base.hpp"

namespace has_castle
{
namespace fixed_point
{

// ================================
// Shift operators
// ================================

// Shift operators do not change the fractional bit count of the fixed
// point number. To change

// Shift left
template <int F, typename T>
constexpr fixed_point<F, T> operator<<(const fixed_point<F, T> &fp, const int &rhs) noexcept
{
    return {fp.raw_value() << rhs, 0};
}

// Shift right
template <int F, typename T>
constexpr fixed_point<F, T> operator>>(const fixed_point<F, T> &fp, const int &rhs) noexcept
{
    return {fp.raw_value() >> rhs, 0};
}

// Assignment shift left
template <int F, typename T>
inline fixed_point<F, T> &operator<<=(fixed_point<F, T> &fp, const int &rhs) noexcept
{
    fp.raw_value() <<= rhs;
    return fp;
}

// Assignment shift right
template <int F, typename T>
inline fixed_point<F, T> &operator>>=(fixed_point<F, T> &fp, const int &rhs) noexcept
{
    fp.raw_value() >>= rhs;
    return fp;
}

// ================================
// Bit operators
// ================================

// Bit operators operate on the raw value directly.

// Bit-and
template <int F, typename T>
constexpr fixed_point<F, T> operator&(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return {lhs.raw_value() & rhs.raw_value(), 0};
}

// Bit-or
template <int F, typename T>
constexpr fixed_point<F, T> operator|(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return {lhs.raw_value() | rhs.raw_value(), 0};
}

// Bit-xor
template <int F, typename T>
constexpr fixed_point<F, T> operator^(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return {lhs.raw_value() ^ rhs.raw_value(), 0};
}

// Bit-negate
template <int F, typename T>
constexpr fixed_point<F, T> operator~(const fixed_point<F, T> &lhs) noexcept
{
    return {~lhs.raw_value(), 0};
}

// Assignment bit-and
template <int F, typename T>
inline fixed_point<F, T> &operator&=(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    lhs.raw_value() &= rhs.raw_value();
    return lhs;
}

// Assignment bit-or
template <int F, typename T>
inline fixed_point<F, T> &operator|=(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    lhs.raw_value() |= rhs.raw_value();
    return lhs;
}

// Assignment bit-xor
template <int F, typename T>
inline fixed_point<F, T> &operator^=(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    lhs.raw_value() ^= rhs.raw_value();
    return lhs;
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__BITOPS_H