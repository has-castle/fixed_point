#ifndef _HAS_CASTLE__FIXED_POINT__STANDARD_TYPES_H
#define _HAS_CASTLE__FIXED_POINT__STANDARD_TYPES_H

#include "base.hpp"

namespace has_castle
{
namespace fixed_point
{

// Fixed width types (exact)

#ifdef INT64_MAX
template <int F>
using fp64_t = fixed_point<F, int64_t>;
#endif

#ifdef UINT64_MAX
template <int F>
using ufp64_t = fixed_point<F, uint64_t>;
#endif

#ifdef INT32_MAX
template <int F>
using fp32_t = fixed_point<F, int32_t>;
#endif

#ifdef UINT32_MAX
template <int F>
using ufp32_t = fixed_point<F, uint32_t>;
#endif

#ifdef INT16_MAX
template <int F>
using fp16_t = fixed_point<F, int16_t>;
#endif

#ifdef UINT16_MAX
template <int F>
using ufp16_t = fixed_point<F, uint16_t>;
#endif

#ifdef INT8_MAX
template <int F>
using fp8_t = fixed_point<F, int8_t>;
#endif

#ifdef UINT8_MAX
template <int F>
using ufp8_t = fixed_point<F, uint8_t>;
#endif

// Fixed-width types (least-n)

template <int F>
using fp_least64_t = fixed_point<F, int_least64_t>;

template <int F>
using ufp_least64_t = fixed_point<F, uint_least64_t>;

template <int F>
using fp_least32_t = fixed_point<F, int_least32_t>;

template <int F>
using ufp_least32_t = fixed_point<F, uint_least32_t>;

template <int F>
using fp_least16_t = fixed_point<F, int_least16_t>;

template <int F>
using ufp_least16_t = fixed_point<F, uint_least16_t>;

template <int F>
using fp_least8_t = fixed_point<F, int_least8_t>;

template <int F>
using ufp_least8_t = fixed_point<F, uint_least8_t>;

// Fixed-width types (fast-n)

template <int F>
using fp_fast64_t = fixed_point<F, int_fast64_t>;

template <int F>
using ufp_fast64_t = fixed_point<F, uint_fast64_t>;

template <int F>
using fp_fast32_t = fixed_point<F, int_fast32_t>;

template <int F>
using ufp_fast32_t = fixed_point<F, uint_fast32_t>;

template <int F>
using fp_fast16_t = fixed_point<F, int_fast16_t>;

template <int F>
using ufp_fast16_t = fixed_point<F, uint_fast16_t>;

template <int F>
using fp_fast8_t = fixed_point<F, int_fast8_t>;

template <int F>
using ufp_fast8_t = fixed_point<F, uint_fast8_t>;

// Misc

template <int F>
using fp_max_t = fixed_point<F, intmax_t>;

template <int F>
using ufp_max_t = fixed_point<F, uintmax_t>;

// Native types

template <int F>
using fp_char_t = fixed_point<F, char>;

template <int F>
using ufp_char_t = fixed_point<F, unsigned char>;

template <int F>
using fp_short_t = fixed_point<F, short>;

template <int F>
using ufp_short_t = fixed_point<F, unsigned short>;

template <int F>
using fp_int_t = fixed_point<F, int>;

template <int F>
using ufp_int_t = fixed_point<F, unsigned int>;

template <int F>
using fp_long_t = fixed_point<F, long>;

template <int F>
using ufp_long_t = fixed_point<F, unsigned long>;

template <int F>
using fp_longlong_t = fixed_point<F, long long>;

template <int F>
using ufp_longlong_t = fixed_point<F, unsigned long long>;

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT__STANDARD_TYPES_H