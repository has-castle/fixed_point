#ifndef _HAS_CASTLE__FIXED_POINT__BITOPS_H
#define _HAS_CASTLE__FIXED_POINT__BITOPS_H

#include "base.hpp"

namespace has_castle
{
namespace fixed_point
{

// ================================
// Bit operators
// ================================

// Bit operators operate on the raw value directly.

// Bit-and
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
constexpr auto operator&(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() & rhs.raw_value())>
{
    return {lhs.raw_value() & rhs.raw_value(), 0};
}

// Bit-or
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
constexpr auto operator|(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() | rhs.raw_value())>
{
    return {lhs.raw_value() | rhs.raw_value(), 0};
}

// Bit-xor
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
constexpr auto operator^(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() ^ rhs.raw_value())>
{
    return {lhs.raw_value() ^ rhs.raw_value(), 0};
}

// Bit-negate
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
constexpr auto operator~(const Lhs &lhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(~lhs.raw_value())>
{
    return {~lhs.raw_value(), 0};
}

// Assignment bit-and
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
inline Lhs &operator&=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() &= rhs.raw_value();
    return lhs;
}

// Assignment bit-or
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
inline Lhs &operator|=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() |= rhs.raw_value();
    return lhs;
}

// Assignment bit-xor
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
inline Lhs &operator^=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() ^= rhs.raw_value();
    return lhs;
}

template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
inline auto operator!(Lhs& lhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(!lhs.raw_value())>
{
    return {!lhs.raw_value(), 0};
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__BITOPS_H