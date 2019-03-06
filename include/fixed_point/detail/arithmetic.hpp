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
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr auto operator+(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() + rhs.raw_value())>
{
    return {lhs.raw_value() + rhs.raw_value(), 0};
}

// Binary subtraction
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr auto operator-(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() - rhs.raw_value())>
{
    return {lhs.raw_value() - rhs.raw_value(), 0};
}

// Assignment plus
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Lhs::frac_bits == Rhs::frac_bits>::type>
inline Lhs &operator+=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() += rhs.raw_value();
    return lhs;
}

// Assignment minus
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Lhs::frac_bits == Rhs::frac_bits>::type>
inline Lhs &operator-=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() -= rhs.raw_value();
    return lhs;
}

// Unary plus
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
constexpr auto operator+(const Lhs lhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(+lhs.raw_value())>
{
    return {+lhs.raw_value(), 0};
}

// Unary minus
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
constexpr auto operator-(const Lhs &lhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(-lhs.raw_value())>
{
    return {-lhs.raw_value(), 0};
}

// ================================
// Arithmetic operators (multiplicative)
// ================================

// Multiplication results in the fractional part being adjusted to sum of
// operands' fractional bit count
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
constexpr auto operator*(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits + Rhs::frac_bits, decltype(lhs.raw_value() * rhs.raw_value())>
{
    return {lhs.raw_value() * rhs.raw_value(), 0};
}

// Multiplication with value_type (usually some integer)
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
constexpr auto operator*(const Lhs &lhs, const typename Lhs::value_type &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() * rhs)>
{
    return {lhs.raw_value() * rhs, 0};
}

// Division results in the fractional part being adjusted to the difference
// of the operands' fractional bit count.
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value>::type>
constexpr auto operator/(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits - Rhs::frac_bits, decltype(lhs.raw_value() / rhs.raw_value())>
{
    return {lhs.raw_value() / rhs.raw_value(), 0};
}

// Division by value_type (usually some integer)
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
constexpr auto operator/(const Lhs &lhs, const typename Lhs::value_type &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() / rhs)>
{
    return {lhs.raw_value() / rhs, 0};
}

// Modulo results in the fractional part being adjusted to the difference
// of the operands' fractional bit count.
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Lhs::frac_bits == Rhs::frac_bits>::type>
constexpr auto operator%(const Lhs &lhs, const Rhs &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() % rhs.raw_value())>
{
    return {lhs.raw_value() % rhs.raw_value(), 0};
}

// Assignment multiplication only works with a right-hand operand that has
// zero fractional bits (otherwise the type would have to change)
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Rhs::frac_bits == 0>::type>
inline Lhs &operator*=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() *= rhs.raw_value();
    return lhs;
}

// Assignment division only works with a right-hand operand that has zero
// fractional bits (otherwise the type would have to change)
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Rhs::frac_bits == 0>::type>
inline Lhs &operator/=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() /= rhs.raw_value();
    return lhs;
}

// Assignment modulo only works with a right-hand operand that has zero
// fractional bits (otherwise the type would have to change)
template <typename Lhs, typename Rhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value && is_fixed_point<Rhs>::value && Lhs::frac_bits == Rhs::frac_bits>::type>
inline Lhs &operator%=(Lhs &lhs, const Rhs &rhs) noexcept
{
    lhs.raw_value() %= rhs.raw_value();
    return lhs;
}

// ================================
// Shift operators
// ================================

// Shift operators do not change the fractional bit count of the fixed
// point number. To change

// Shift left
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
constexpr auto operator<<(const Lhs &lhs, const int &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() << rhs)>
{
    return {lhs.raw_value() << rhs, 0};
}

// Shift right
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
constexpr auto operator>>(const Lhs &lhs, const int &rhs) noexcept
    -> fixed_point<Lhs::frac_bits, decltype(lhs.raw_value() >> rhs)>
{
    return {lhs.raw_value() >> rhs, 0};
}

// Assignment shift left
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
inline Lhs &operator<<=(Lhs &lhs, const int &rhs) noexcept
{
    lhs.raw_value() <<= rhs;
    return lhs;
}

// Assignment shift right
template <typename Lhs, typename = typename std::enable_if<is_fixed_point<Lhs>::value>::type>
inline Lhs &operator>>=(Lhs &lhs, const int &rhs) noexcept
{
    lhs.raw_value() >>= rhs;
    return lhs;
}

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__ARITHMETIC_H