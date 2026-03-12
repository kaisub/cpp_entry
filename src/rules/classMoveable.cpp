#include <iostream>
#include <format>
#include <utility>

#include "rules/classMoveable.h"

using std::cout;

Movable::Movable(int value)
{
    cout << std::format("Movable construct: {}\n", value);
    data = new int(value);
}

Movable::Movable(std::string name) : name(std::move(name))
{
    cout << std::format("Movable construct with name: {}\n", this->name);
}

Movable::operator const std::string&() const
{
    cout << std::format("->Movable operator const std::string&: {}<- ", name);
    return name;
}

Movable::Movable(const Movable& other)
{
    cout << std::format("Movable copy construct: {} ", other.getValue());
    name = other.name;
    if (other.data != nullptr) {
        data = new int(*other.data);
    }
}

Movable::Movable(Movable&& other) noexcept
{
    std::printf("Movable move construct: %d\n", other.getValue());
    data = other.data;
    other.data = nullptr;
}

Movable::~Movable()
{
    delete data;
}

int Movable::getValue() const
{
    return data != nullptr ? *data : 0;
}

void fun(const Movable& other)
{
    cout << "fun taking const ref: " << other.getValue() << '\n';
    // Calls copy constructor
    Movable copy = other;//NOLINT(performance-unnecessary-copy-initialization)
}

void fun(Movable&& other)
{
    cout << "fun taking rvalue ref: " << other.getValue() << '\n';
    Movable moved = std::move(other); // Calls move constructor
}

void demonstrateClassMoveable()
{
    cout << "*** printMove ***" << '\n';
    Movable mo1(42);
    Movable mo2(mo1);  // Copy constructor
    Movable mo3(std::move(mo1));  // Move constructor

    cout << '\n';
    Movable mo4(100);
    fun(mo4); // Calls fun(const Movable&)
    cout << '\n';
    fun(Movable(200)); // Calls fun(Movable&&)
    cout << '\n';

    // conversion to Movable, then move constructor
    // Movable mo6 = static_cast<Movable>(300);

    Movable mo7 = static_cast<Movable>(std::string("mo7"));
    cout << "mo7 name: " << static_cast<const std::string&>(mo7) << '\n';

    // lambda capture by copy -> const construct
    [=]() {
        std::cout << "copy lambda: " << mo7.getValue() << '\n';
    }();
    // lambda capture by const ref -> no new object
    [&ref = std::as_const(mo7)]() {
        std::cout << "move lambda: " << ref.getValue() << '\n';
    }();
    cout << '\n';
}
