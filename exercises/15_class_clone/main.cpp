#include "../exercise.h"

// READ: 复制构造函数
// https://zh.cppreference.com/w/cpp/language/copy_constructor
// READ: 显式弃置
// https://zh.cppreference.com/w/cpp/language/function

class DynFibonacci {
    size_t *cache;
    int cached;
    int capacity;   // ★ 必须记录容量，才能正确复制

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity)
        : cache(new size_t[capacity]), cached(2), capacity(capacity) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 复制构造器：深拷贝
    DynFibonacci(DynFibonacci const &other)
        : cache(new size_t[other.capacity]),
          cached(other.cached),
          capacity(other.capacity) {
        for (int i = 0; i < cached; ++i) {
            cache[i] = other.cache[i];
        }
    }

    // 析构器：释放资源
    ~DynFibonacci() {
        delete[] cache;
    }

    // 非 const 版本：可推进缓存
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }

    // const 版本：只读访问
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = fib;   
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");

    return 0;
}
