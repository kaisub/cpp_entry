#pragma once

#include <span>

#include "functionality.h"

// Interface to decouple logic from direct function calls
class IFunctionalityDispatcher {
public:
    virtual ~IFunctionalityDispatcher() = default;
    virtual void onDummyEntry() = 0;
    virtual void onRulesEntry(Functionality func) = 0;
};

// Overload for testing (Dependency Injection)
class FunctionalityDispatcher : public IFunctionalityDispatcher {
public:
    void onDummyEntry() override;
    void onRulesEntry(Functionality func) override;
};
