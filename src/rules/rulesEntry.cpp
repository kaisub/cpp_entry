#include <iostream>

#include "rules/classArrays.h"
#include "rules/classInheritance.h"
#include "rules/classMoveable.h"
#include "rules/lambdas.h"
#include "rules/rulesEntry.h"
#include "rules/smartPointers.h"
#include "rules/templates.h"
#include "rules/tupples.h"

using std::cout;

void rulesEntry(Functionality funct)
{
    switch (funct) {
    case Functionality::Templates:
        demonstrateTempates();
        break;
    case Functionality::Tupples:
        demonstrateTupples();
        break;

    case Functionality::ClassArrays:
        demonstrateClassArrays();
        break;

    case Functionality::ClassInheritance:
        demonstrateClassInheritance();
        break;

    case Functionality::ClassMoveable:
        demonstrateClassMoveable();
        break;

    case Functionality::Lambdas:
        demonstrateLambdas();
        break;

    case Functionality::SmartPointers:
        demonstrateSmartPointers();
        break;

    default:
        cout << "unhandled functionality: " << static_cast<int>(funct) << '\n';
        break;
    }
}
