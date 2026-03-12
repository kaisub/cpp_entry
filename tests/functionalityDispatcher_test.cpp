#include <gtest/gtest.h>
#include <iostream>
#include <magic_enum.hpp>
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
    // Iterate over all values defined in the Functionality enum
    for (auto func : magic_enum::enum_values<Functionality>()) {

        // Skip DummyExamples since it is handled by a different method (onDummyEntry)
        if (func == Functionality::DummyExamples) {
            continue;
        }

        // Verify that executing onRulesEntry for each standard rule does not throw exceptions.
        // The << operator appends the specific enum name to the error log if the test fails.
        EXPECT_NO_THROW({
            dispatcher.onRulesEntry(func);
        }) << "Exception thrown during onRulesEntry for: " << magic_enum::enum_name(func);
    }
}
