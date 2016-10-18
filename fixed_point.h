#ifndef _HAS_CASTLE__FIXED_POINT_H
#define _HAS_CASTLE__FIXED_POINT_H

#include <type_traits>

namespace has_castle {
namespace fixed_point {

template<int F, typename T = int>
struct fixed_point {
    using value_type = T;
    using frac_bits = std::integral_constant<int, F>;

    value_type raw_value;

    //
    // Default constructors and constructing from fixed_point type
    //
    // Default constructor initializes to zero
    constexpr fixed_point() noexcept : raw_value(0) {}
    // 
    constexpr fixed_point(const fixed_point<frac_bits::value, value_type>& other) = default;

    // Constructor
    constexpr fixed_point(value_type value) noexcept : raw_value(value) {}

    constexpr inline operator value_type() const noexcept {
        return raw_value;
    }
}; // struct fixed_point

} // namespace fixed_point
} // namespace has_castle

#endif // _HAS_CASTLE__FIXED_POINT_H
