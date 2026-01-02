#include "../exercise.h"
#include <utility>

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;

public:
    // 构造器：动态分配缓存并初始化
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]),
          cached(1),
          capacity(capacity) {
        ASSERT(capacity >= 2, "capacity must be >= 2");
        cache[0] = 0;
        cache[1] = 1;
    }

    // 移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept
        : cache(other.cache),
          cached(other.cached),
          capacity(other.capacity) {
        other.cache = nullptr;
        other.cached = -1;
        other.capacity = 0;
    }

    // 移动赋值运算符（处理自移动）
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] cache;

        cache = other.cache;
        cached = other.cached;
        capacity = other.capacity;

        other.cache = nullptr;
        other.cached = -1;
        other.capacity = 0;

        return *this;
    }

    // 析构器
    ~DynFibonacci() {
        delete[] cache;
    }

    // 非 const 访问：按需计算
    size_t operator[](int i) {
        ASSERT(i < capacity, "i out of capacity");
        for (; cached < i; ++cached) {
            cache[cached + 1] = cache[cached] + cache[cached - 1];
        }
        return cache[i];
    }

    // const 访问：只读
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // 对象是否仍然持有资源
    bool is_alive() const {
        return cache != nullptr;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);   // 自移动必须安全
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
