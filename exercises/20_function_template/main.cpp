#include "../exercise.h"
#include <type_traits>
#include <cmath>

// READ: 函数模板
// https://zh.cppreference.com/w/cpp/language/function_template


template <typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");

    ASSERT(std::fabs(plus(0.1, 0.2) - 0.3) < 1e-9,
           "How to make this pass?");

    return 0;
}
