#include <gtest/gtest.h>
#include <iostream>
#include <magic_enum.hpp>
#include <sstream>
#include <string>

#include "functionalityDispatcher.h"

// We can't mock the global ::dummyEntry() easily.
// The best we can do for basic coverage is ensure it runs and doesn't crash/throw.
// This assumes ::dummyEntry() is safe to call in a test environment.

class FunctionalityDispatcherTest : public ::testing::Test {
protected:
    FunctionalityDispatcher dispatcher;
};

TEST_F(FunctionalityDispatcherTest, FunctionalityExecutesWithoutThrowing) {
    // Iterate over all values defined in the Functionality enum
    for (auto funct : magic_enum::enum_values<Functionality>()) {

        // Verify that executing onRulesEntry for each standard rule does not throw exceptions.
        // The << operator appends the specific enum name to the error log if the test fails.
        switch (functionalityIsOfType(funct)) {
            case FunctionalityType::Dummy:
                EXPECT_NO_THROW({ dispatcher.onDummyEntry(); }) << "Exception thrown during onDummyEntry";
                break;

            case FunctionalityType::Rules:
                EXPECT_NO_THROW({ dispatcher.onRulesEntry(funct); }) <<
                "Exception thrown during onRulesEntry for: " << magic_enum::enum_name(funct);
                break;
            case FunctionalityType::Algorithms:
                EXPECT_NO_THROW({ dispatcher.onAlgorithmsEntry(funct); }) <<
                "Exception thrown during onAlgorithmsEntry for: " << magic_enum::enum_name(funct);
                break;
            case FunctionalityType::None:
                break;
        }
    }
}

TEST(FunctionalityIsOfTypeTest, CorrectlyCategorizesFunctionality) {
    // Test Dummy type
    EXPECT_EQ(functionalityIsOfType(Functionality::DummyExamples), FunctionalityType::Dummy);

    // Test Rules types
    EXPECT_EQ(functionalityIsOfType(Functionality::ClassArrays), FunctionalityType::Rules);
    EXPECT_EQ(functionalityIsOfType(Functionality::ClassInheritance), FunctionalityType::Rules);
    EXPECT_EQ(functionalityIsOfType(Functionality::ClassMoveable), FunctionalityType::Rules);
    EXPECT_EQ(functionalityIsOfType(Functionality::SmartPointers), FunctionalityType::Rules);
    EXPECT_EQ(functionalityIsOfType(Functionality::Tupples), FunctionalityType::Rules);

    // Test Algorithms types
    EXPECT_EQ(functionalityIsOfType(Functionality::DummyAlgorithm), FunctionalityType::Algorithms);

    // Test default/None case for an unknown value
    EXPECT_EQ(functionalityIsOfType(static_cast<Functionality>(999)), FunctionalityType::None);
}
