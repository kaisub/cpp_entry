#include "functionality.h"
#include "algorithms/algorithmsEntry.h"
#include "algorithms/printDir.h"
#include <iostream>

using std::cout;

void algorithmsEntry(Functionality funct)
{
    switch(funct) {
        case Functionality::PrintDir:
            demonstratePrintDir();
            break;
    default:
    cout << "unhandled functionality: " << static_cast<int>(funct) << '\n';
        break;
    }
}
