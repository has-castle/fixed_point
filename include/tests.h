#ifndef _HAS_CASTLE__FIXED_POINT__TESTS_H
#define _HAS_CASTLE__FIXED_POINT__TESTS_H

#include "catch.hpp"
#include "fixed_point/fixed_point.hpp"
#include <cstdint>

using namespace has_castle::fixed_point;

using uf16p16_t = fixed_point<16, uint32_t>;
using f15p16_t  = fp32_t<16>;
using f7p24_t   = fp32_t<16>;
using f23p8_t   = fp32_t<8>;
using f7p8_t    = fixed_point<8, int16_t>;
using uf24p8_t  = fixed_point<8, uint32_t>;
using q8_t      = fixed_point<8>;

#endif // _HAS_CASTLE__FIXED_POINT__TESTS_H
