#include "tests.h"

TEST_CASE("Additive operators", "[additive][operator_plus][operator_minus]")
{
    SECTION("Add")
    {
        auto q0 = q8_t{1.5};
        auto q1 = q8_t{1.5};
        auto q2 = q0 + q1;
        CHECK(q2 == decltype(q1){3.0});

        auto q3 = q8_t{-1.5};
        auto q4 = q0 + q3;
        CHECK(q4 == decltype(q4){0.0});

        q0 += q1;
        CHECK(q0 == decltype(q0){3.0});
    }

    SECTION("Subtract")
    {
        auto q0 = q8_t{1.5};
        auto q1 = q8_t{0.5};
        auto q2 = q0 - q1;
        CHECK(q2 == decltype(q2){1.0});

        auto q3 = q8_t{-0.5};
        auto q4 = q0 - q3;
        CHECK(q4 == decltype(q4){2.0});

        q0 -= q1;
        CHECK(q0 == decltype(q0){1.0});
    }
}

TEST_CASE("Multiplicative operators", "[multiplicative][operator_mul][operator_div]")
{
    SECTION("Multiply")
    {
        auto q0 = q8_t{1.5};
        auto q1 = q8_t{2};
        auto q2 = q0 * q1;
        CHECK(q2 == decltype(q2){3.0});

        q0 *= fixed_point<0>{2};
        CHECK(q0 == decltype(q0){3.0});
    }

    SECTION("Divide")
    {
        // Same precision
        {
            auto q0 = q8_t{1.5};
            auto q1 = q8_t{0.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){3.0});
        }
        {
            auto q0 = q8_t{0.5};
            auto q1 = q8_t{1.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){1.0 / 3.0});
        }
        {
            auto q0 = q8_t{-1.5};
            auto q1 = q8_t{0.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){-3.0});
        }
        {
            auto q0 = q8_t{1.5};
            auto q1 = q8_t{-0.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){-3.0});
            auto q3 = q2 * q1;
            CHECK(q3 == q0);
        }
        // Different precision (hi/lo)
        {
            auto q0 = f15p16_t{1.5};
            auto q1 = q8_t{0.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){3.0});
        }
        {
            auto q0 = f15p16_t{0.5};
            auto q1 = q8_t{1.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){1.0 / 3.0});
        }
        {
            auto q0 = f15p16_t{-1.5};
            auto q1 = q8_t{0.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){-3.0});
        }
        {
            auto q0 = f15p16_t{1.5};
            auto q1 = q8_t{-0.5};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){-3.0});
            auto q3 = q2 * q1;
            CHECK(q3 == q0);
        }
        // Different precision (lo/hi)
        // Caution: this causes precision to go into a territory of negative
        // fractional bits where the maximum precision is a positive power of 2.
        {
            auto q0 = q8_t{1.5};
            auto q1 = f15p16_t{0.0005};
            auto q2 = q0 / q1;
            // This wouldn't work by comparing to double-initialized value
            // because initializing from double rounds while the native
            // division doesn't
            CHECK(q2 == decltype(q2){3000});
        }
        {
            auto q0 = q8_t{-1.5};
            auto q1 = f15p16_t{0.0005};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){-2816});
        }
        {
            auto q0 = q8_t{1.5};
            auto q1 = f15p16_t{-1. / 1024};
            auto q2 = q0 / q1;
            CHECK(q2 == decltype(q2){-1024 * 1.5});
            auto q3 = q2 * q1;
            CHECK(q3 == q0);
        }
        // Equals-divide operator
        {
            auto q0 = q8_t{3.0};
            auto q1 = fixed_point<0>{2};
            q0 /= q1;
            CHECK(q0 == decltype(q0){1.5});
        }
    }

    SECTION("Modulo")
    {
        {
            auto q0 = q8_t{1.5};
            auto q1 = q8_t{1};
            auto q2 = q0 % q1;
            CHECK(q2 == decltype(q2){0.5});
        }
        {
            auto q0 = q8_t{1.5};
            auto q1 = fixed_point<16>{1};
            auto q2 = q0 % q8_t{q1};
            CHECK(q2 == decltype(q2){0.5});
        }
        {
            auto q0 = q8_t{1.5};
            auto q1 = q8_t{1.1};
            auto q2 = q0 % q1;
            CHECK(q2 == decltype(q2){0.4});
        }
        {
            auto q0 = q8_t{1.5};
            auto q1 = q8_t{-1};
            auto q2 = q0 % q1;
            CHECK(q2 == decltype(q2){0.5});
        }
        {
            auto q0 = q8_t{-1.5};
            auto q1 = q8_t{1};
            auto q2 = q0 % q1;
            CHECK(q2 == decltype(q2){-0.5});
        }
        {
            auto q0 = q8_t{1.5};
            auto q1 = fixed_point<0>{-1};
            auto q2 = q0 % q8_t{q1};
            CHECK(q2 == decltype(q2){0.5});
        }
        {
            auto q0 = q8_t{1.5};
            auto q1 = fixed_point<16>{-1};
            auto q2 = q0 % q8_t{q1};
            CHECK(q2 == decltype(q2){0.5});
        }
        {
            auto q0 = q8_t{-1.5};
            auto q1 = fixed_point<0>{1};
            auto q2 = q0 % q8_t{q1};
            CHECK(q2 == decltype(q2){-0.5});
        }
        {
            auto q0 = q8_t{-1.5};
            auto q1 = fixed_point<16>{1};
            auto q2 = q0 % q8_t{q1};
            CHECK(q2 == decltype(q2){-0.5});
        }
    }
}

TEST_CASE("Shift operators", "[shift][operator_shl][operator_shr]")
{
    SECTION("Left shift")
    {
        auto q0 = q8_t{1.0};
        auto q1 = q0 << 1;
        REQUIRE(q1 == decltype(q1){2.0});
        q0 <<= 2;
        REQUIRE(q0 == decltype(q0){4.0});
    }
    SECTION("Right shift")
    {
        auto q0 = q8_t{1.0};
        auto q1 = q0 >> 1;
        REQUIRE(q1 == decltype(q1){0.5});
        q0 >>= 2;
        REQUIRE(q0 == decltype(q0){0.25});
    }
}