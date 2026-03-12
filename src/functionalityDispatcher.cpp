#include <span>

#include "dummy/dummyFunc.h"
#include "functionalityDispatcher.h"
#include "rules/rulesEntry.h"

void FunctionalityDispatcher::onDummyEntry() { dummyEntry(); }

void FunctionalityDispatcher::onRulesEntry(Functionality func) {
  rulesEntry(func);
}
