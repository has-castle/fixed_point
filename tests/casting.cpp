#include "tests.h"

TEST_CASE("Casting", "[cast][operator_value_type][operator_bool]")
{
    SECTION("value_type cast")
    {
        auto q0 = q8_t{1};
        REQUIRE(static_cast<int>(q0) == 1);
    }

    SECTION("bool cast")
    {
        auto q0 = q8_t{1};
        CHECK(static_cast<bool>(q0) == true);

        auto q1 = q8_t{-1};
        CHECK(static_cast<bool>(q1) == true);

        auto q2 = q8_t{0};
        CHECK(static_cast<bool>(q2) == false);
    }

    SECTION("template<T2> cast")
    {
        auto q0 = q8_t{1.5f};
        auto f0 = static_cast<float>(q0);
        CHECK(1.499f < f0);
        CHECK(f0 < 1.501f);

        auto q1 = q8_t{-1.5f};
        auto f1 = static_cast<float>(q1);
        CHECK(-1.499f > f1);
        CHECK(f1 > -1.501f);
    }
}