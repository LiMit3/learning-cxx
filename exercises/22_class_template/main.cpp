#include "../exercise.h"
#include <cstring>

// READ: 类模板
// https://zh.cppreference.com/w/cpp/language/class_template

template <class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // 1️⃣ 复制 shape 并计算总元素个数
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 单向广播加法
    Tensor4D &operator+=(Tensor4D const &others) {
        // 2️⃣ 计算 each dimension 的 stride
        unsigned int stride_this[4];
        unsigned int stride_other[4];

        stride_this[3] = 1;
        stride_other[3] = 1;
        for (int i = 2; i >= 0; --i) {
            stride_this[i] = stride_this[i + 1] * shape[i + 1];
            stride_other[i] = stride_other[i + 1] * others.shape[i + 1];
        }

        // 3️⃣ 遍历 this 的所有元素
        unsigned int total = 1;
        for (int i = 0; i < 4; ++i) {
            total *= shape[i];
        }

        for (unsigned int idx = 0; idx < total; ++idx) {
            // 将线性 index 转为 4D index
            unsigned int rem = idx;
            unsigned int index_other = 0;

            for (int d = 0; d < 4; ++d) {
                unsigned int coord = rem / stride_this[d];
                rem %= stride_this[d];

                // 单向广播：others 该维为 1 则使用 0
                unsigned int other_coord =
                    (others.shape[d] == 1) ? 0 : coord;

                index_other += other_coord * stride_other[d];
            }

            data[idx] += others.data[index_other];
        }
        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        unsigned int s1[]{1, 2, 3, 1};
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
