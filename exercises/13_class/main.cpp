#include "../exercise.h"

// C++ 中，`class` 和 `struct` 之间的唯一区别是默认访问控制
// READ: 访问说明符 <https://zh.cppreference.com/w/cpp/language/access>

class Fibonacci {
    size_t cache[16];
    int cached;

public:
    // 构造器：负责初始化私有成员，避免 UB
    Fibonacci() : cache{0, 1}, cached(2) {}

    // 缓存优化的斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 有无参构造器，声明即完成初始化
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
