#include <iostream>

#include "rules/classInheritance.h"
#include "rules/classMoveable.h"
#include "rules/rulesEntry.h"
#include "rules/smartPointers.h"

using std::cout;

void rulesEntry(Functionality functionality) {
  switch (functionality) {
  case Functionality::ClassInheritance: {
    demonstrateClassInheritance();
  } break;

  case Functionality::ClassMoveable: {
    demonstrateClassMoveable();
  } break;

  case Functionality::SmartPointers: {
    demonstrateSmartPointers();
  } break;

  default:
    cout << "unhandled functionality: " << static_cast<int>(functionality)
         << '\n';
    break;
  }
}
