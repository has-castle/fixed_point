#ifndef _HAS_CASTLE__FIXED_POINT__UTIL_H
#define _HAS_CASTLE__FIXED_POINT__UTIL_H

#include <type_traits>

namespace has_castle
{
namespace fixed_point
{
namespace detail
{

template <typename T>
constexpr auto builtin_shr(T value, int amount) noexcept
    -> decltype(value >> amount)
{
    return value >> amount;
}

template <typename T>
struct uses_arithmetic_shift : std::integral_constant<bool, builtin_shr(T(-1), 1) == -1>
{
};

template <typename T = int>
constexpr T shift_by_portable(T value, typename std::enable_if<std::is_signed<T>::value, int>::type amount) noexcept
{
    // Note shifting by a negative value or shifting a negative value is
    // undefined. We avoid this here.
    return value < 0 ? amount < 0 ? ~(~value >> -amount) : -(-value << amount) : amount < 0 ? value >> -amount : value << amount;
}

template <typename T = unsigned>
constexpr T shift_by_portable(T value, typename std::enable_if<std::is_unsigned<T>::value, int>::type amount) noexcept
{
	// Note shifting by a negative value or shifting a negative value is
	// undefined. We avoid this here.
	return amount < 0 ? value >> -amount : value << amount;
}

template <typename T = int>
constexpr T shift_by_arithmetic(T value, int amount) noexcept
{
    // Only call when arithmetic shifting of negative values is used.
    return amount < 0 ? value >> -amount : value << amount;
}

template <typename T = int>
constexpr T shift_by(T value, int amount) noexcept
{
    return uses_arithmetic_shift<T>::value ? shift_by_arithmetic(value, amount) : shift_by_portable(value, amount);
}

// Returns value / (2 ** exp) with the precision of T and allowing negative exp.
template <typename T>
static constexpr T div_by_exp(T value, int exp) noexcept
{
    // Here we replace exponentiation with shifting in a well-defined way and
    // using division or multiplication appropriately.
    return exp < 0 ? value * (1 << -exp) : value / (1 << exp);
}

} // namespace detail

template <typename T>
struct is_fixed_point : std::false_type
{
};

// template <typename T>
// static inline const bool is_fixed_point_v = is_fixed_point<T>::value;

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__UTIL_H
