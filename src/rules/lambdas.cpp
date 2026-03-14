#include "rules/lambdas.h"
#include <iostream>

using std::cout;

struct Baz {
    [[nodiscard]] auto foo() const {
        return [*this] { cout << s << '\n'; };
    }
    // C++23: 'self' is a copy of the object, captured by value
    // static auto foo2(this Baz self) {
    //     return [self = std::move(self)] { std::cout << self.s << '\n'; };
    // }
    std::string s;
};

void useWithTempObjects()
{
    constexpr auto square_lambda = [](auto val) { return val * val; };
    static_assert(square_lambda(5) == 25, "Square lambda failed");

    auto f01 = Baz{"Hello"}.foo();
    f01();
    // auto f02 = Baz{"World"}.foo2();
    // f02();
}

void demonstrateLambdas()
{
    useWithTempObjects();
}
