cmake_minimum_required(VERSION 3.9)
project(stlhc_fixed_point LANGUAGES CXX VERSION 0.1)

add_library(stlhc_fixed_point INTERFACE)
target_sources(stlhc_fixed_point
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include/fixed_point/fixed_point.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/arithmetic.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/base.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/bit_ops.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/comparison.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/numeric_limits.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/standard_types.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/stream.hpp
        ${PROJECT_SOURCE_DIR}/include/fixed_point/detail/util.hpp
)
target_compile_features(stlhc_fixed_point INTERFACE cxx_std_11)
target_include_directories(stlhc_fixed_point INTERFACE ${PROJECT_SOURCE_DIR}/include)

add_executable(stlhc_fixed_point_tests ${PROJECT_SOURCE_DIR}/tests/main.cpp)
target_sources(stlhc_fixed_point_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/tests/arithmetic.cpp
        ${PROJECT_SOURCE_DIR}/tests/casting.cpp
        ${PROJECT_SOURCE_DIR}/tests/comparison.cpp
        ${PROJECT_SOURCE_DIR}/tests/constructors.cpp
        ${PROJECT_SOURCE_DIR}/tests/main.cpp
)
target_link_libraries(stlhc_fixed_point_tests PRIVATE stlhc_fixed_point)
target_include_directories(stlhc_fixed_point_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_test(unittest stlhc_fixed_point_tests)
