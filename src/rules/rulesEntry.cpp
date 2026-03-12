#include <iostream>

#include "rules/rulesEntry.h"
#include "rules/classInheritance.h"
#include "rules/smartPointers.h"

using std::cout;

void rulesEntry(Functionality functionality)
{
    switch (functionality)
    {
    case Functionality::ClassInheritance: {
        demonstrateClassInheritance();
    } break;

    case Functionality::SmartPointers: {
        demonstrateSmartPointers();
    }
    default:
        break;
    }
}
