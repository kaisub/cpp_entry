#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>

#include "functionalityDispatcher.h"
#include "functionality.h"

// We can't mock the global ::dummyEntry() easily.
// The best we can do for basic coverage is ensure it runs and doesn't crash/throw.
// This assumes ::dummyEntry() is safe to call in a test environment.

class FunctionalityDispatcherTest : public ::testing::Test {
protected:
    FunctionalityDispatcher dispatcher;
};

TEST_F(FunctionalityDispatcherTest, DummyEntryExecutesWithoutThrowing) {
    EXPECT_NO_THROW(dispatcher.onDummyEntry());
}

TEST_F(FunctionalityDispatcherTest, RulesEntryExecutesWithoutThrowing) {
    EXPECT_NO_THROW({ dispatcher.onRulesEntry(Functionality::ClassInheritance); });
    EXPECT_NO_THROW({ dispatcher.onRulesEntry(Functionality::SmartPointers); });
}
