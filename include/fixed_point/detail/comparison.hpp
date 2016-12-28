#ifndef _HAS_CASTLE__FIXED_POINT__COMPARISON_H
#define _HAS_CASTLE__FIXED_POINT__COMPARISON_H

#include "base.hpp"

namespace has_castle
{
namespace fixed_point
{

// ================================
// Comparison operators
// ================================

template <typename Lhs, typename Rhs, typename = typename std::enable_if<Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr bool operator<(const Lhs &lhs, const Rhs &rhs) noexcept
{
    return lhs.raw_value() < rhs.raw_value();
}

template <typename Lhs, typename Rhs, typename = typename std::enable_if<Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr bool operator>(const Lhs &lhs, const Rhs &rhs) noexcept
{
    return lhs.raw_value() > rhs.raw_value();
}

template <typename Lhs, typename Rhs, typename = typename std::enable_if<Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr bool operator<=(const Lhs &lhs, const Rhs &rhs) noexcept
{
    return lhs.raw_value() <= rhs.raw_value();
}

template <typename Lhs, typename Rhs, typename = typename std::enable_if<Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr bool operator>=(const Lhs &lhs, const Rhs &rhs) noexcept
{
    return lhs.raw_value() >= rhs.raw_value();
}

template <typename Lhs, typename Rhs, typename = typename std::enable_if<Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr bool operator==(const Lhs &lhs, const Rhs &rhs) noexcept
{
    return lhs.raw_value() == rhs.raw_value();
}

template <typename Lhs, typename Rhs, typename = typename std::enable_if<Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr bool operator!=(const Lhs &lhs, const Rhs &rhs) noexcept
{
    return lhs.raw_value() != rhs.raw_value();
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__COMPARISON_H