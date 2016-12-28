#ifndef _HAS_CASTLE__FIXED_POINT__NUMERIC_LIMITS_H
#define _HAS_CASTLE__FIXED_POINT__NUMERIC_LIMITS_H

#include <limits>
#include "base.hpp"

using namespace has_castle::fixed_point;

namespace std
{

template <int F, typename T>
struct numeric_limits<fixed_point<F, T>>
{
    using fp = fixed_point<F, T>;
    using lim = numeric_limits<T>;
    
    static constexpr bool is_specialized = true;
    static constexpr bool is_signed = lim::is_signed;
    static constexpr bool is_integer = (F <= 0);
    static constexpr bool is_exact = lim::is_exact;
    static constexpr bool has_infinity = lim::has_infinity;
    static constexpr bool has_quiet_NaN = lim::has_quiet_NaN;
    static constexpr bool has_signaling_NaN = lim::has_signaling_NaN;
    static constexpr float_denorm_style has_denorm = lim::has_denorm;
    static constexpr bool has_denorm_loss = lim::has_denorm_loss;
    static constexpr bool round_style = lim::round_style;
    static constexpr bool is_iec559 = lim::is_iec559;
    static constexpr bool is_bounded = lim::is_bounded;
    static constexpr bool is_modulo = lim::is_modulo;
    static constexpr bool digits = lim::digits;
    static constexpr bool digits10 = lim::digits10;
    static constexpr bool max_digits10 = lim::max_digits10;
    static constexpr int radix = lim::radix;
    static constexpr int min_exponent = lim::min_exponent;
    static constexpr int min_exponent10 = lim::min_exponent10;
    static constexpr int max_exponent = lim::max_exponent;
    static constexpr int max_exponent10 = lim::max_exponent10;
    static constexpr bool traps = lim::traps;
    static constexpr bool tinyness_before = lim::tinyness_before;

    static constexpr fp min() noexcept { return {lim::min(), 0}; }
    static constexpr fp lowest() noexcept { return {lim::lowest(), 0}; }
    static constexpr fp max() noexcept { return {lim::max(), 0}; }
    static constexpr fp epsilon() noexcept { return {lim::epsilon(), 0}; }
    static constexpr fp round_error() noexcept { return {lim::round_error(), 0}; }
    static constexpr fp infinity() noexcept { return {lim::infinity(), 0}; }
    static constexpr fp quiet_NaN() noexcept { return {lim::quiet_NaN(), 0}; }
    static constexpr fp signaling_NaN() noexcept { return {lim::signaling_NaN(), 0}; }
    static constexpr fp denorm_min() noexcept { return {lim::denorm_min(), 0}; }
};

} // namespace std

#endif // _HAS_CASTLE__FIXED_POINT__NUMERIC_LIMITS_H
