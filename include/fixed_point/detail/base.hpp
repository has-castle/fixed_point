#ifndef _HAS_CASTLE__FIXED_POINT__BASE_H
#define _HAS_CASTLE__FIXED_POINT__BASE_H

#include <type_traits>
#include <limits>
#include <iostream>
#include <cstdint>

namespace has_castle
{
namespace fixed_point
{

template <typename T = int>
constexpr T shift_by(T value, int amount) noexcept
{
    // Note shifting by a negative value or shifting a negative value is
    // undefined. We avoid this here.
    return value < 0 ? amount < 0 ? -(-value >> -amount) : -(-value << amount) : amount < 0 ? value >> -amount : value << amount;
}

// Returns value / (2 ** exp) with the precision of T and allowing negative exp.
template <typename T>
static constexpr T div_by_exp(T value, int exp) noexcept
{
    // Here we replace exponentiation with shifting in a well-defined way and
    // using division or multiplication appropriately.
    return exp < 0 ? value * (1 << -exp) : value / (1 << exp);
}

template <int F, typename T = int>
struct fixed_point
{
    // The underlying value type of the fixed_point number
    using value_type = T;
    // The type of the entire fixed_point structure.
    using this_type = fixed_point<F, T>;
    // The number of fractional bits in the fixed_point number
    using frac_bits = std::integral_constant<int, F>;
    // The number of integer bits int the fixed_point number
    using int_bits = std::integral_constant<int, std::numeric_limits<value_type>::digits - frac_bits::value>;
    // Check validity of template parameters.
    static_assert(std::is_integral<value_type>::value, "T must be integral type.");

  private:
    value_type raw_value_;

    static constexpr value_type frac_mask() noexcept
    {
        return frac_bits::value <= 0 ? 0 : int_bits::value <= 0 ? ~0 : ((1 << (frac_bits::value)) - 1);
    }

  public:
    // ================================
    // Constructors
    // ================================

    // Default constructor initializes to zero
    constexpr fixed_point() noexcept : raw_value_(0) {}

    // Default copy constructor
    constexpr fixed_point(const fixed_point &other) = default;

    // Default assignment operator
    fixed_point &operator=(const fixed_point &other) = default;

    // Default destructor
    ~fixed_point() = default;

    // Value-type constructor, value parameter specifies the int_part.
    constexpr explicit fixed_point(value_type int_part) noexcept
        : raw_value_(shift_by(int_part, frac_bits::value)) {}

    // Constructor based on other fixed_point<> type with same value_type
    // This can be used for conversion between
    template <int F_other>
    constexpr explicit fixed_point(const fixed_point<F_other, value_type> &other) noexcept
        : raw_value_(shift_by(other.raw_value(), frac_bits::value - F_other)) {}

    // Constructor based on other fixed_point<> type with same number of fractional bits
    template <typename T_other>
    constexpr explicit fixed_point(const fixed_point<frac_bits::value, T_other> &other) noexcept
        : raw_value_(static_cast<value_type>(other.raw_value())) {}

    // Generic constructor, works with float, double or long double with
    // rounding.
    template <typename T0>
    constexpr explicit fixed_point(T0 value) noexcept
        : raw_value_(static_cast<value_type>(
              div_by_exp(value +
                             static_cast<T0>(div_by_exp(value >= 0 ? 0.5 : -0.5,
                                                        frac_bits::value)),
                         -frac_bits::value))) {}

    // Raw constructor, initializes the internal raw value by the raw_value
    // parameter and shift it left by the amount specified by shift.
    // This is not explicit because it can't be called indirectly by accident
    // and enables us to omit the type before a return statement when using
    // this constructor.
    constexpr fixed_point(value_type raw_value, int shift) noexcept
        : raw_value_(shift_by(raw_value, shift)) {}

    // ================================
    // Access methods
    // ================================

    // Raw value as const reference
    constexpr const value_type &raw_value() const noexcept
    {
        return /*const_cast<typename std::add_const<value_type &>::type>*/ (raw_value_);
    }

    // Raw value as reference, can't be const or constexpr
    inline value_type &raw_value() noexcept
    {
        return raw_value_;
    }

    // Integer part
    constexpr value_type int_part() const noexcept
    {
        return shift_by(raw_value(), -frac_bits::value);
    }

    // Fractional part
    constexpr value_type frac_part() const noexcept
    {
        return raw_value() & frac_mask();
    }

    // ================================
    // Cast operators
    // ================================

    // Cast to value_type
    constexpr explicit operator value_type() const noexcept
    {
        // Returning the int part is consistent with the value_type constructor.
        // This way any integer that is representable by the fixed_point type
        // can do a roundtript between integer, fixed_point and integer variables.
        // This is also how floating point type casting works.
        return int_part();
    }

    // Cast to bool
    constexpr explicit operator bool() const noexcept
    {
        static_assert(std::is_convertible<value_type, bool>::value,
                      "The value_type must be convertible to bool.");
        //
        return static_cast<bool>(raw_value());
    }

    // Explicit cast to any other type raw_value can be static_casted to.
    template <typename T2>
    constexpr explicit operator T2() const noexcept
    {
        static_assert(std::is_convertible<value_type, T2>::value,
                      "The value_type must be convertible to T2 template type.");
        // See operator value_type() cast. Returning the integer part is the
        // consistent choice with respect to the constructors.
        return div_by_exp(static_cast<T2>(raw_value()), frac_bits::value);
    }

    // ================================
    // Arithmetic operators (additive)
    // ================================

    // Binary addition
    constexpr fixed_point operator+(const fixed_point &rhs) const noexcept
    {
        return {raw_value() + rhs.raw_value(), 0};
    }

    // Binary subtraction
    constexpr fixed_point operator-(const fixed_point &rhs) const noexcept
    {
        return {raw_value() - rhs.raw_value(), 0};
    }

    // Assignment plus
    inline fixed_point &operator+=(const fixed_point &rhs) noexcept
    {
        raw_value() += rhs.raw_value();
        return *this;
    }

    // Assignment minus
    inline fixed_point &operator-=(const fixed_point &rhs) noexcept
    {
        raw_value() -= rhs.raw_value();
        return *this;
    }

    // Unary plus
    constexpr fixed_point operator+() const noexcept
    {
        return *this;
    }

    // Unary minus
    constexpr fixed_point operator-() const noexcept
    {
        return {-raw_value(), 0};
    }

    // ================================
    // Arithmetic operators (multiplicative)
    // ================================

    // Multiplication results in the fractional part being adjusted to sum of
    // operands' fractional bit count
    template <int F_rhs, typename T_rhs>
    constexpr auto operator*(const fixed_point<F_rhs, T_rhs> &rhs) const noexcept
        -> fixed_point<frac_bits::value + F_rhs, decltype(raw_value() * rhs.raw_value())>
    {
        return {raw_value() * rhs.raw_value(), 0};
    }

    // Division results in the fractional part being adjusted to the difference
    // of the operands' fractional bit count.
    template <int F_rhs, typename T_rhs>
    constexpr auto operator/(const fixed_point<F_rhs, T_rhs> &rhs) const noexcept
        -> fixed_point<frac_bits::value - F_rhs, decltype(raw_value() / rhs.raw_value())>
    {
        //static_assert(F_rhs <= frac_bits::value,
        //              "The divisor of the division must have lower precision"
        //              "(fewer fractional bits) than the dividend.");
        //
        return {raw_value() / rhs.raw_value(), 0};
    }

    // Modulo results in the fractional part being adjusted to the difference
    // of the operands' fractional bit count.
    template <int F_rhs, typename T_rhs>
    constexpr auto operator%(const fixed_point<F_rhs, T_rhs> &rhs) const noexcept
        -> fixed_point<frac_bits::value, value_type>
    {
        return {raw_value() % this_type{rhs}.raw_value(), 0};
    }

    // Assignment multiplication only works with a right-hand operand that has
    // zero fractional bits (otherwise the type would have to change)
    inline fixed_point &operator*=(const fixed_point<0, value_type> &rhs) noexcept
    {
        raw_value() *= rhs.raw_value();
        return *this;
    }

    // Assignment division only works with a right-hand operand that has zero
    // fractional bits (otherwise the type would have to change)
    inline fixed_point &operator/=(const fixed_point<0, value_type> &rhs) noexcept
    {
        raw_value() /= rhs.raw_value();
        return *this;
    }

    // Assignment modulo only works with a right-hand operand that has zero
    // fractional bits (otherwise the type would have to change)
    template <int F_rhs, typename T_rhs>
    inline fixed_point &operator%=(const fixed_point<F_rhs, T_rhs> &rhs) noexcept
    {
        raw_value() %= this_type{rhs}.raw_value();
        return *this;
    }

    // ================================
    // Comparison operators
    // ================================

    constexpr bool operator<(const fixed_point &rhs) const noexcept
    {
        return raw_value() < rhs.raw_value();
    }

    constexpr bool operator>(const fixed_point &rhs) const noexcept
    {
        return raw_value() > rhs.raw_value();
    }

    constexpr bool operator<=(const fixed_point &rhs) const noexcept
    {
        return raw_value() <= rhs.raw_value();
    }

    constexpr bool operator>=(const fixed_point &rhs) const noexcept
    {
        return raw_value() >= rhs.raw_value();
    }

    constexpr bool operator==(const fixed_point &rhs) const noexcept
    {
        return raw_value() == rhs.raw_value();
    }

    constexpr bool operator!=(const fixed_point &rhs) const noexcept
    {
        return raw_value() != rhs.raw_value();
    }

}; // struct fixed_point

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__BASE_H
