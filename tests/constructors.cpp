#include "tests.h"

TEST_CASE("Basics", "[types]")
{
    SECTION("Bit counts")
    {
        auto f1 = uf24p8_t::frac_bits;
        REQUIRE(f1 == 8);
        auto i1 = uf24p8_t::int_bits;
        REQUIRE(i1 == 24);

        auto f2 = f15p16_t::frac_bits;
        REQUIRE(f2 == 16);
        auto i2 = f15p16_t::int_bits;
        REQUIRE(i2 == 15);
    }

    SECTION("Type checking")
    {
        using is_same_q8_t = std::is_same<q8_t::value_type, int>;
        REQUIRE(is_same_q8_t::value);

        using is_same_uf24p8_t = std::is_same<uf24p8_t::value_type, uint32_t>;
        REQUIRE(is_same_uf24p8_t::value);
    }

    SECTION("shift_by")
    {
        for (int32_t v = std::numeric_limits<int8_t>::min(); static_cast<int32_t>(v) <= std::numeric_limits<int8_t>::max(); v++) {
            for (auto a = -7; a < 8; a++) {
                auto port = detail::shift_by_portable<int8_t>(v, a);
                auto arit = detail::shift_by_arithmetic<int8_t>(v, a);
                REQUIRE(port == arit);
            }
        }
    }
}

TEST_CASE("Constructors", "[constructors][raw_value][int_part][frac_part]")
{
    SECTION("Default constructor, raw_value")
    {
        auto q0 = q8_t{};
        REQUIRE(q0.raw_value() == 0);
    }

    SECTION("Value-type constructor, raw_value and {int,frac}_part")
    {
        q8_t q0{1};
        REQUIRE(q0.raw_value() == (1 << 8));
        REQUIRE(q0.int_part() == 1);
        REQUIRE(q0.frac_part() == 0);

        q8_t q1{-1};
        REQUIRE(q1.int_part() == -1);
        REQUIRE(q1.frac_part() == 0);
    }

    SECTION("fixed_point<F_other> constructor")
    {
        auto q0 = f7p24_t{1};
        auto q1 = f15p16_t{q0};
        CHECK(q1.int_part() == q0.int_part());
        CHECK(q1.frac_part() == q0.frac_part());

        auto q2 = f15p16_t{1};
        auto q3 = f7p24_t{q2};
        CHECK(q3.int_part() == q2.int_part());
        CHECK(q3.frac_part() == q2.frac_part());

        auto q4 = f7p24_t{-1};
        auto q5 = f15p16_t{q4};
        CHECK(q5.int_part() == q4.int_part());
        CHECK(q5.frac_part() == q4.frac_part());

        auto q6 = f15p16_t{-1};
        auto q7 = f7p24_t{q6};
        CHECK(q7.int_part() == q6.int_part());
        CHECK(q7.frac_part() == q6.frac_part());
    }

    SECTION("fixed_point<T_other> constructor")
    {
        auto q0 = f15p16_t{1};
        auto q1 = uf16p16_t{q0};
        CHECK(q1.int_part() == q0.int_part());
        CHECK(q1.frac_part() == q0.frac_part());

        auto q2 = f23p8_t{1};
        auto q3 = f7p8_t{q2};
        CHECK(q3.int_part() == q2.int_part());
        CHECK(q3.frac_part() == q2.frac_part());

        auto q4 = f7p8_t{1};
        auto q5 = f23p8_t{q4};
        CHECK(q5.int_part() == q4.int_part());
        CHECK(q5.frac_part() == q4.frac_part());
    }

    SECTION("Generic constructor")
    {
        auto q0 = fixed_point<1>{1.5};
        CHECK(q0.int_part() == 1);
        CHECK(q0.frac_part() == 1);

        auto q1 = fixed_point<1>{1.5f};
        CHECK(q1.int_part() == 1);
        CHECK(q1.frac_part() == 1);

        auto q2 = fixed_point<1>{1.25001f};
        CHECK(q2.int_part() == 1);
        CHECK(q2.frac_part() == 1);

        auto q3 = fixed_point<1>{1.24999f};
        CHECK(q3.int_part() == 1);
        CHECK(q3.frac_part() == 0);

        auto q4 = q8_t{short{1}};
        CHECK(q4.int_part() == 1);
        CHECK(q4.frac_part() == 0);

        auto q5 = fixed_point<1>{-1.5f};
        CHECK(q5.raw_value() == -3);
        CHECK(q5.int_part() == -2);
        CHECK(q5.frac_part() == 1);

        auto q6 = fixed_point<1>{-0.5};
        CHECK(q6.raw_value() == -1);
        CHECK(q6.int_part() == -1);
        CHECK(q6.frac_part() == 1);

        auto q7 = fixed_point<2>{-0.5};
        CHECK(q7.raw_value() == -2);
        CHECK(q7.int_part() == -1);
        CHECK(q7.frac_part() == 2);

        auto q8 = fixed_point<2>{-100.5};
        CHECK(q8.raw_value() == -402);
        CHECK(q8.int_part() == -101);
        CHECK(q8.frac_part() == 2);

        auto q9 = fixed_point<1>{-100.5};
        CHECK(q9.raw_value() == -201);
        CHECK(q9.int_part() == -101);
        CHECK(q9.frac_part() == 1);

        auto q10 = fixed_point<1, int8_t>{-63};
        CHECK(q10.raw_value() == -126);
        CHECK(q10.int_part() == -63);
        CHECK(q10.frac_part() == 0);

        auto q11 = fixed_point<1, int8_t>{-63.5};
        CHECK(q11.raw_value() == -127);
        CHECK(q11.int_part() == -64);
        CHECK(q11.frac_part() == 1);

    }

    SECTION("Defaulted constructors and operators")
    {
        auto q0 = q8_t{1};
        auto q1 = q8_t{q0};
        CHECK(q1.int_part() == q0.int_part());
        CHECK(q1.frac_part() == q0.frac_part());

        auto q2 = q0;
        CHECK(q2.int_part() == q0.int_part());
        CHECK(q2.frac_part() == q0.frac_part());
    }
}
