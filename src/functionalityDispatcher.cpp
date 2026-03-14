#include <span>

#include "functionalityDispatcher.h"
#include "algorithms/algorithmsEntry.h"
#include "dummy/dummyFunc.h"
#include "rules/rulesEntry.h"

void FunctionalityDispatcher::onDummyEntry() {
    dummyEntry();
}

void FunctionalityDispatcher::onRulesEntry(Functionality funct) {
    rulesEntry(funct);
}

void FunctionalityDispatcher::onAlgorithmsEntry(Functionality funct) {
    algorithmsEntry(funct);
}
