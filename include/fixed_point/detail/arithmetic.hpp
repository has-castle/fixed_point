#ifndef _HAS_CASTLE__FIXED_POINT__ARITHMETIC_H
#define _HAS_CASTLE__FIXED_POINT__ARITHMETIC_H

#include "base.hpp"

namespace has_castle
{
namespace fixed_point
{

// ================================
// Arithmetic operators (additive)
// ================================

// Binary addition
template <int F, typename T>
constexpr fixed_point<F, T> operator+(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return {lhs.raw_value() + rhs.raw_value(), 0};
}

// Binary subtraction
template <int F, typename T>
constexpr fixed_point<F, T> operator-(const fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    return {lhs.raw_value() - rhs.raw_value(), 0};
}

// Assignment plus
template <int F, typename T>
inline fixed_point<F, T> &operator+=(fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    lhs.raw_value() += rhs.raw_value();
    return lhs;
}

// Assignment minus
template <int F, typename T>
inline fixed_point<F, T> &operator-=(fixed_point<F, T> &lhs, const fixed_point<F, T> &rhs) noexcept
{
    lhs.raw_value() -= rhs.raw_value();
    return lhs;
}

// Unary plus
template <int F, typename T>
constexpr fixed_point<F, T> operator+(const fixed_point<F, T> lhs) noexcept
{
    return lhs;
}

// Unary minus
template <int F, typename T>
constexpr fixed_point<F, T> operator-(const fixed_point<F, T> lhs) noexcept
{
    return {-lhs.raw_value(), 0};
}

// ================================
// Arithmetic operators (multiplicative)
// ================================

// Multiplication results in the fractional part being adjusted to sum of
// operands' fractional bit count
template <int F_lhs, typename T_lhs, int F_rhs, typename T_rhs>
constexpr auto operator*(const fixed_point<F_lhs, T_lhs> &lhs, const fixed_point<F_rhs, T_rhs> &rhs) noexcept
    -> fixed_point<F_lhs + F_rhs, decltype(lhs.raw_value() * rhs.raw_value())>
{
    return {lhs.raw_value() * rhs.raw_value(), 0};
}

// Division results in the fractional part being adjusted to the difference
// of the operands' fractional bit count.
template <int F_lhs, typename T_lhs, int F_rhs, typename T_rhs>
constexpr auto operator/(const fixed_point<F_lhs, T_lhs> &lhs, const fixed_point<F_rhs, T_rhs> &rhs) noexcept
    -> fixed_point<F_lhs - F_rhs, decltype(lhs.raw_value() * rhs.raw_value())>
{
    //static_assert(F_rhs <= frac_bits::value,
    //              "The divisor of the division must have lower precision"
    //              "(fewer fractional bits) than the dividend.");
    //
    return {lhs.raw_value() / rhs.raw_value(), 0};
}

// Modulo results in the fractional part being adjusted to the difference
// of the operands' fractional bit count.
template <int F_lhs, typename T_lhs, int F_rhs, typename T_rhs>
constexpr auto operator%(const fixed_point<F_lhs, T_lhs> &lhs, const fixed_point<F_rhs, T_rhs> &rhs) noexcept
    -> fixed_point<F_lhs, T_lhs>
{
    return {lhs.raw_value() % fixed_point<F_lhs, T_lhs>{rhs}.raw_value(), 0};
}

// Assignment multiplication only works with a right-hand operand that has
// zero fractional bits (otherwise the type would have to change)
template <int F, typename T>
inline fixed_point<F, T> &operator*=(fixed_point<F, T> &lhs, const fixed_point<0, T> &rhs) noexcept
{
    lhs.raw_value() *= rhs.raw_value();
    return lhs;
}

// Assignment division only works with a right-hand operand that has zero
// fractional bits (otherwise the type would have to change)
template <int F, typename T>
inline fixed_point<F, T> &operator/=(fixed_point<F, T> &lhs, const fixed_point<0, T> &rhs) noexcept
{
    lhs.raw_value() /= rhs.raw_value();
    return lhs;
}

// Assignment modulo only works with a right-hand operand that has zero
// fractional bits (otherwise the type would have to change)
template <int F_lhs, typename T_lhs, int F_rhs, typename T_rhs>
inline fixed_point<F_lhs, T_lhs> &operator%=(fixed_point<F_lhs, T_lhs> &lhs, const fixed_point<F_rhs, T_rhs> &rhs) noexcept
{
    lhs.raw_value() %= fixed_point<F_lhs, T_lhs>{rhs}.raw_value();
    return lhs;
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__ARITHMETIC_H