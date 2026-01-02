#include "../exercise.h"
#include <vector>

// READ: std::vector<bool>
// READ: 模板特化

int main(int argc, char **argv) {
    std::vector<bool> vec(100, true); // size = 100, all bits = true
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");

    // NOTICE: 平台相关！Ubuntu 下 std::vector<bool> 通常为 40 字节
    std::cout << "sizeof(std::vector<bool>) = "
              << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == sizeof(std::vector<bool>), "Fill in the correct value.");

    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        auto ref = vec[30];   // ⚠ 不是 bool&，而是 proxy
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // ref 修改的是位代理，直接影响 vec
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}
