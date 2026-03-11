#include <iostream>
#include <cstdio> // Required for std::puts

#include "rules/classInheritance.h"

using std::cout;

void demonstrateClassInheritance()
{
    cout << "\nDemonstrating class inheritance and abstract interfaces\n\n";
    AA val{10, 20};
    val.print();
}

Base::Base(int val) : val(val) {}
// LCOV_EXCL_START
Base::~Base()
{
    std::puts("~Base::destructor\n");
};
// LCOV_EXCL_STOP
void Base::print() const
{
    cout << "Base::print() a = " << val << '\n';
}
// LCOV_EXCL_START
AbstractInterfaceOne::~AbstractInterfaceOne()
{
    std::puts("~AbstractInterfaceOne::destructor\n");
};

AbstractInterfaceTwo::~AbstractInterfaceTwo()
{
    std::puts("~AbstractInterfaceTwo::destructor\n");
};
// LCOV_EXCL_STOP
AA::AA(int valX, int valY, int valA) : Base(valA), valX(valX), valY(valY) {}
// LCOV_EXCL_START
AA::~AA()
{
    std::puts("~AA::destructor\n");
}
// LCOV_EXCL_STOP
void AA::interfacePrintOne() const
{
    cout << "AA::interfacePrintOne() called" << '\n';
}

void AA::interfacePrintTwo() const
{
    cout << "AA::interfacePrintTwo() called" << '\n';
}

void AA::print() const
{
    cout << "*** AA::print() ***" << '\n';

    Base::print();
    interfacePrintOne();
    interfacePrintTwo();
    cout << "x: " << valX << " y: " << valY << " a: " << val << '\n';

    cout << '\n';
}
