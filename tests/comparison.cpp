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

TEST_CASE("Comparison", "[comparison][operator_lt][operator_le][operator_gt][operator_ge]")
{
    SECTION("Lt operator")
    {
        auto q0 = q8_t{1.0};
        auto q1 = q8_t{2.0};
        auto q2 = q1;
        REQUIRE(q0 < q1);
        REQUIRE(!(q1 < q2));
        REQUIRE(!(q1 < q0));
    }
    SECTION("Le operator")
    {
        auto q0 = q8_t{1.0};
        auto q1 = q8_t{2.0};
        auto q2 = q1;
        REQUIRE(q0 <= q1);
        REQUIRE(q1 <= q2);
        REQUIRE(!(q1 <= q0));
    }
    SECTION("Gt operator")
    {
        auto q0 = q8_t{2.0};
        auto q1 = q8_t{1.0};
        auto q2 = q1;
        REQUIRE(q0 > q1);
        REQUIRE(!(q1 > q2));
        REQUIRE(!(q1 > q0));
    }
    SECTION("Ge operator")
    {
        auto q0 = q8_t{2.0};
        auto q1 = q8_t{1.0};
        auto q2 = q1;
        REQUIRE(q0 >= q1);
        REQUIRE(q1 >= q2);
        REQUIRE(!(q1 >= q0));
    }
}
