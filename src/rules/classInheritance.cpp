#include <cstdio> // Required for std::puts
#include <iostream>

#include "rules/classInheritance.h"

using std::cout;

void demonstrateClassInheritance() {
  cout << "\nDemonstrating class inheritance and abstract interfaces\n\n";
  AA val{10, 20};
  val.print();
}

Base::Base(int val) : val(val) {}

// Kept on a single line so the CI coverage regex (.*~.*) excludes the entire
// destructor (including braces) at once.
Base::~Base() { std::puts("~Base::destructor\n"); };

void Base::print() const { cout << "Base::print() a = " << val << '\n'; }

// Kept on a single line so the CI coverage regex (.*~.*) excludes the entire
// destructor (including braces) at once.
AbstractInterfaceOne::~AbstractInterfaceOne() { std::puts("~AbstractInterfaceOne::destructor\n"); };

// Kept on a single line so the CI coverage regex (.*~.*) excludes the entire
// destructor (including braces) at once.
AbstractInterfaceTwo::~AbstractInterfaceTwo() { std::puts("~AbstractInterfaceTwo::destructor\n"); };

AA::AA(int valX, int valY, int valA) : Base(valA), valX(valX), valY(valY) {}

// Kept on a single line so the CI coverage regex (.*~.*) excludes the entire
// destructor (including braces) at once.
AA::~AA() { std::puts("~AA::destructor\n"); }

void AA::interfacePrintOne() const {
  cout << "AA::interfacePrintOne() called" << '\n';
}

void AA::interfacePrintTwo() const {
  cout << "AA::interfacePrintTwo() called" << '\n';
}

void AA::print() const {
  cout << "*** AA::print() ***" << '\n';

  Base::print();
  interfacePrintOne();
  interfacePrintTwo();
  cout << "x: " << valX << " y: " << valY << " a: " << val << '\n';

  cout << '\n';
}
