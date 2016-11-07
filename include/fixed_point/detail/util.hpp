#ifndef _HAS_CASTLE__FIXED_POINT__UTIL_H
#define _HAS_CASTLE__FIXED_POINT__UTIL_H

namespace has_castle
{
namespace fixed_point
{
namespace detail
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

} // namespace detail
} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__UTIL_H
