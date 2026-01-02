#include "../exercise.h"
#include <cstring>

// READ: 模板非类型实参

template<unsigned int N, class T>
struct Tensor {
    unsigned int shape[N];
    T *data;

    Tensor(unsigned int const shape_[N]) {
        unsigned int size = 1;
        // 填入 shape 并计算总元素数
        for (unsigned int i = 0; i < N; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::memset(data, 0, size * sizeof(T));
    }

    ~Tensor() {
        delete[] data;
    }

    // 为了保持简单，禁止复制和移动
    Tensor(Tensor const &) = delete;
    Tensor(Tensor &&) noexcept = delete;

    T &operator[](unsigned int const indices[N]) {
        return data[data_index(indices)];
    }
    T const &operator[](unsigned int const indices[N]) const {
        return data[data_index(indices)];
    }

private:
    unsigned int data_index(unsigned int const indices[N]) const {
        unsigned int index = 0;
        unsigned int stride = 1;
        // 行优先（C-order）线性化
        for (int i = N - 1; i >= 0; --i) {
            ASSERT(indices[i] < shape[i], "Invalid index");
            index += indices[i] * stride;
            stride *= shape[i];
            if (i == 0) break;  // 防止无符号下溢
        }
        return index;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{2, 3, 4, 5};
        auto tensor = Tensor<4, int>(shape);

        unsigned int i0[]{0, 0, 0, 0};
        tensor[i0] = 1;
        ASSERT(tensor[i0] == 1, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1, "tensor[i0] should be 1");

        unsigned int i1[]{1, 2, 3, 4};
        tensor[i1] = 2;
        ASSERT(tensor[i1] == 2, "tensor[i1] should be 2");
        ASSERT(tensor.data[119] == 2, "tensor[i1] should be 2");
    }
    {
        unsigned int shape[]{7, 8, 128};
        auto tensor = Tensor<3, float>(shape);

        unsigned int i0[]{0, 0, 0};
        tensor[i0] = 1.f;
        ASSERT(tensor[i0] == 1.f, "tensor[i0] should be 1");
        ASSERT(tensor.data[0] == 1.f, "tensor[i0] should be 1");

        unsigned int i1[]{3, 4, 99};
        tensor[i1] = 2.f;
        ASSERT(tensor[i1] == 2.f, "tensor[i1] should be 2");
        ASSERT(tensor.data[3683] == 2.f, "tensor[i1] should be 2");
    }
    return 0;
}
