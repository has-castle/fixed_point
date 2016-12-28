# Has-castle Fixed point C++ library

![Build status](https://travis-ci.org/has-castle/fixed_point.svg?branch=master)

## About

This is a C++11 library that is useful when performing fixed-point arithmetic on integer numbers. This library provides type safety, and easy to use methods with no overhead.

Using fixed point arithmetic is recommended when floating point arithmetic is too slow or does not provide the required precision for the application. A typical use case might be embedded systems with no or only single-precision floating point ALUs.

[Read more about fixed point numbers below.](#about-fixed-point-arithmetic)

## Demo

```C++
#include "fixed_point/fixed_point.hpp"
using namespace has_castle::fixed_point::types;

// Define a 29.2 and 19.12 format constant.
//      - fp32_t defines total width and signedness (backed by int32_t)
//      - template parameter is number of fractional bits
// Values compiled to single integer constant (constexpr constructors)
const auto Kp        = fp32_t<2>{10.25}; // Control loop constant
const auto Sens_conv = fp32_t<12>{1. / 45.5}; // Sensor constant
int r_setpoint, u_control;

// Demonstrate a control loop working with fixed point values
void control_fixp()
{
    // y is fp32_t<12> == fp32_t<12> * fp32_t<0>
    // Multiplication and division adjust the result precision, not the value
    auto y = Sens_conv * fp32_t<0>{sensordata};
    // e is fp32_t<12> == fp32_t<12> - fp32_t<12>
    // Addition and subtraction require the same precision
    // r_setpoint is type int but constructing fp32_t<12> does the required shift
    auto e = fp32_t<12>{r_setpoint} - y;
    // u is fp32_t<10> == fp32_t<10>{fp32_t<12> * fp32_t<2>}
    //                 == fp32_t<10>{fp32_t<14>}
    // The fp32_t<10> constructor does the right shift by >> 4 from the fp32_t<14>
    auto u = fp32_t<10>{e * Kp};
    // Casting to int or any other type preserves semantic value
    // i.e., here, we get the integer part of u.
    u_control = static_cast<int>(u);
}

int main()
{
    // Simulating a small control loop
    for (;;)
    {
        // r_setpoint is set somewhere
        control_fixp();
    }
    return 0;
}
```

## Features

### No-overhead type support

The library provides wrapper types most builtin integral types and all run-time arithmetic operations are performed directly on the underlying types without runtime overhead. Type information comprises the underlying type and the precision. Some examples:

```C++
#include "fixed_point.h"
using namespace has_castle::fixed_point::types;
using has_castle::fixed_point::fixed_point; // Only required for d0, usually not needed
                        // backing type
fixed_point<7, int> d0; // user-define (int in this case)
fp32_t<16>          d1; // int32_t
ufp16_t<7>          d2; // uint16_t
fp_least32_t<31>    d3; // int_least32_t, smallest type with at least 32 bits
ufp_fast16_t<15>    d4; // uint_fast16_t, fastest native type with at least 16 bits
ufp_max_t<10>       d5; // uint_max_t, widest native integer type
fp_char_t<5>        d6; // char
ufp_short_t<5>      d7; // unsigned short
fp_int_t<5>         d8; // int
fp_long_t<5>        d9; // long
ufp_longlong_t<5>   d10; // unsigned long long
```

### Compile-time expansion of values

All constructors are `constexpr` meaning that constants get compiled to a single integer backing value. Conversion from floating point types is supported. There is no need to manually convert any value to a fixed point representation.

```C++
fp32_t<10> d0a;
auto d0b = fp32_t<10>{};    // Default-constructed values are initialized to zero.
auto d1 = fp32_t<16>{10};   // Contruct from native, backing value is (10 << 16)
auto d2 = fp32_t<-8>{1024}; // Supports negative fractional bits without undefined behavior
                            // backing value is (1024 >> 8)
auto d3 = fp32_t<8>{d1};    // Construct from different-precision fixed point
                            // backing value is (10 << 8)
auto d4 = fp32_t<16>{3.1416}; // Construct from any type convertible to the backing type
    // integer part will be 3, fractional part closest to 0.1416 (rounded well)
auto d5 = fp64_t<16>{0xBEEF, 13} // Raw constructor: backing value will be (0xBEEF << 13)
```

### Add and subtract

`operator+`, `-`, `+=`, `-=` work with any fixed_point type that has the same fractional precision.

### Multiply and divide

`operator*`, `/` work with any other fixed_point type. The result type has the correct fractional precision (the sum or difference of the fractional precision of the operands for multiplication and division respectively) that might be different than any operand's fractional precision. To obtain a different fractional precision, construct the desired fixed_point type (this will do the required value shifting).

`operator*=`, `/=` only work with the right-hand operand having zero bits of fractional precision because otherwise the result type would change and changing the type of a variable is prohibited in C++.

### Modulo

`operator%` and `%=` only works as expected when the native `operator%` is applied to the underlying type when the precision of the right-hand operand is the same as the left-hand. Here an additional shift is introduced to support all fractional precisions.

## Other libraries to consider

A list of other fixed-point arithmetic or related implementations follow. These can be considered either as replacement or complementary libraries to be used with this one.

* [fixed_point Numerics Library (@johnmcfarlane)](https://github.com/johnmcfarlane/fixed_point) -- replacement -- header-only C++11 library with a standard library proposal (see link)
* [C++14 Fixed Point Library (@mizvekov)](https://github.com/mizvekov/fp) -- replacement -- header-only C++14 with adapters for Boost multiprecision, rational and David Stone's bounded_integer.
* [Fixed Point Class (PeterSchregle on CodeProject)](http://www.codeproject.com/Articles/37636/Fixed-Point-Class) -- replacement/complementary -- Provides fixed point algorithms
* [Bounded integer (David Stone)](https://bitbucket.org/davidstone/bounded_integer) -- complementary -- Compile-time bounds checking with optional runtime checks

## About fixed point arithmetic

> In computing, a fixed-point number representation is a real data type for a number that has a fixed number of digits after (and sometimes also before) the radix point (after the decimal point '.' in English decimal notation). – [_Wikipedia_](https://en.wikipedia.org/wiki/Fixed-point_arithmetic)

For example let's choose an `8.8` format. (8 bits integer part, 8 bits fractional part.) The number 3.75 in this format is represented in binary as `0x03C0` or `960` decimal. The `0x03` is recognizable as the integer part and `0xC0` is the fractional part with the two highest bits set. The bits represent 1/2, 1/4, 1/8 etc. respectively and 0.75 is 1/2 + 1/4.

### Representation

Mathematically fixed point number can be represented by integers that are 2^f times the represented value (i.e., 960 = 3.75 * 2^8) and interpreting a fixed point value the other way is just as easy.

In most circumstances (including this library) fixed point numbers are backed by integer number and all operations are done on that number but the intepretation of the result as a fixed point number defines the operatios as fixed point arithmetic.

### Precision

The precision of integer, fixed point and floating point arithmetic is compared in this subsection.

Integer representation offers the same precision over the entire value range (every integer number but nothing more is representable).

Floating point representation offers good precision over a wide range of values. A value of one or two billionth-of-a-billionth is representable as well as one or two billion-billion. But the two might not be used together because the precision is a function of the magnitude of the value. For example, representing 100'000'001 is not possible with the common C++ `float` type (IEEE binary32 format) because the precision at that value is less than what is needed to represent every integer value. [Read more on Wikipedia.](https://en.wikipedia.org/wiki/IEEE_floating_point)