#include "../exercise.h"

// READ: 静态字段
// READ: 虚析构函数

struct A {
    inline static int num_a = 0;

    A() {
        ++num_a;
    }

    virtual ~A() {   // ★ 关键：虚析构
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

struct B final : public A {
    inline static int num_b = 0;

    B() {
        ++num_b;
    }

    ~B() override {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;

    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;

    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;

    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // ★ 正确的向下转型
    B &bb = dynamic_cast<B &>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // 不修改这里
    delete ab;

    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
