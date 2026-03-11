#include <iostream>

#include "rules/rulesEntry.h"

using std::cout;

void rulesEntry(Functionality functionality)
{
    switch (functionality)
    {
    case Functionality::Inheritance:
        cout << "Inheritance rules not implemented yet.\n";
        break;
    
    default:
        break;
    }
}
