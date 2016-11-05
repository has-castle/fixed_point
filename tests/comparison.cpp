#include "tests.h"

TEST_CASE("Equality", "[equality][operator_eq][operator_neq]")
{
    SECTION("Eq operator")
    {
        auto q0 = q8_t{1.5};
        auto q1 = q8_t{1.5};
        REQUIRE(q0 == q1);
    }

    SECTION("Ne operator")
    {
        auto q0 = q8_t{1.0};
        auto q1 = q8_t{1.5};
        REQUIRE(q0 != q1);
    }
}
