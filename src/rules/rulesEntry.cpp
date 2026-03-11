#include <iostream>

#include "rules/rulesEntry.h"
#include "rules/classInheritance.h"

using std::cout;

void rulesEntry(Functionality functionality)
{
    switch (functionality)
    {
    case Functionality::Inheritance: {
        demonstrateClassInheritance();
    } break;

    default:
        break;
    }
}
