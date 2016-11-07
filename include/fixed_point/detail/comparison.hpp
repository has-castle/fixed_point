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

template <int F, typename T>
constexpr bool operator<(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return lhs.raw_value() < rhs.raw_value();
}

template <int F, typename T>
constexpr bool operator>(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return lhs.raw_value() > rhs.raw_value();
}

template <int F, typename T>
constexpr bool operator<=(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return lhs.raw_value() <= rhs.raw_value();
}

template <int F, typename T>
constexpr bool operator>=(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return lhs.raw_value() >= rhs.raw_value();
}

template <int F, typename T>
constexpr bool operator==(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return lhs.raw_value() == rhs.raw_value();
}

template <int F, typename T>
constexpr bool operator!=(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return lhs.raw_value() != rhs.raw_value();
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__COMPARISON_H