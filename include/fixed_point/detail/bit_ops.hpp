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
template <typename Lhs>
constexpr auto operator<<(const Lhs &lhs, const int &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() << rhs)>
{
    return {lhs.raw_value() << rhs, 0};
}

// Shift right
template <typename Lhs>
constexpr auto operator>>(const Lhs &lhs, const int &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() >> rhs)>
{
    return {lhs.raw_value() >> rhs, 0};
}

// Assignment shift left
template <typename Lhs>
inline Lhs &operator<<=(Lhs &lhs, const int &rhs) noexcept
{
    lhs.raw_value() <<= rhs;
    return lhs;
}

// Assignment shift right
template <typename Lhs>
inline Lhs &operator>>=(Lhs &lhs, const int &rhs) noexcept
{
    lhs.raw_value() >>= rhs;
    return lhs;
}

// ================================
// Bit operators
// ================================

// Bit operators operate on the raw value directly.

// Bit-and
template <typename Lhs, typename Rhs>
constexpr auto operator&(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() & rhs.raw_value())>
{
    return {lhs.raw_value() & rhs.raw_value(), 0};
}

// Bit-or
template <typename Lhs, typename Rhs>
constexpr auto operator|(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() | rhs.raw_value())>
{
    return {lhs.raw_value() | rhs.raw_value(), 0};
}

// Bit-xor
template <typename Lhs, typename Rhs>
constexpr auto operator^(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() ^ rhs.raw_value())>
{
    return {lhs.raw_value() ^ rhs.raw_value(), 0};
}

// Bit-negate
template <typename Lhs>
constexpr auto operator~(const Lhs &lhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(~lhs.raw_value())>
{
    return {~lhs.raw_value(), 0};
}

// Assignment bit-and
template <typename Lhs, typename Rhs>
inline Lhs &operator&=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() &= rhs.raw_value();
    return lhs;
}

// Assignment bit-or
template <typename Lhs, typename Rhs>
inline Lhs &operator|=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() |= rhs.raw_value();
    return lhs;
}

// Assignment bit-xor
template <typename Lhs, typename Rhs>
inline Lhs &operator^=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() ^= rhs.raw_value();
    return lhs;
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__BITOPS_H