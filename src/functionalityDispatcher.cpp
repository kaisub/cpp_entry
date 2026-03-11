#include <span>

#include "functionalityDispatcher.h"
#include "dummy/dummyFunc.h"
#include "rules/rulesEntry.h"

void FunctionalityDispatcher::onDummyEntry()
{
    dummyEntry();
}

void FunctionalityDispatcher::onRulesEntry(Functionality func)
{
    rulesEntry(func);
}
