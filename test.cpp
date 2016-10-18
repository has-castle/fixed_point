#include "fixed_point.h"
#include <iostream>

using namespace has_castle::fixed_point;

int main() {
    
    fixed_point<16> fp;
    std::cout << "Raw value: " << fp.raw_value << std::endl;
    return 0;
}
