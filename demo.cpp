#include "fixed_point.h"
#include <iostream>
#include <cstdint>

using has_castle::fixed_point::fixed_point;

using uf24p8_t = fixed_point<8, uint32_t>;
using f15p16_t = fixed_point<16, int32_t>;
using f7p24_t = fixed_point<24, int32_t>;
using q8_t = fixed_point<8>;

int main()
{
    {
        auto qb = f15p16_t{1};
        auto q0 = f7p24_t{qb};
        std::cout << "qb: " << qb << std::endl;
        std::cout << "q0: " << q0 << std::endl;
    }
    {
        auto q0 = q8_t{1.5};
        auto q1 = fixed_point<0>{1};
        auto q2 = q0 % q1;
        std::cout << "q2: " << q2 << std::endl;
        auto q3 = q8_t{3};
        auto q4 = q0 % q3;
        std::cout << "q4: " << q4 << std::endl;
    }
    {
        auto q0 = q8_t{1.5};
        auto q1 = fixed_point<0>{1};
        auto q2 = q0 / q1;
        std::cout << "q2: " << q2 << std::endl;
        auto q3 = q8_t{3};
        auto q4 = fixed_point<16>(q0) / q3;
        std::cout << "q4: " << q4 << std::endl;
    }
    return 0;
}
