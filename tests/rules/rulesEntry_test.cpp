#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>

#include "rules/rulesEntry.h"
#include "functionality.h"

class RulesEntryTest : public ::testing::Test {
protected:
    std::stringstream buffer;
    std::streambuf* old_cout_buffer = nullptr;

    void SetUp() override {
        // Redirect std::cout to our stringstream buffer
        old_cout_buffer = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        // Restore original std::cout
        std::cout.rdbuf(old_cout_buffer);
    }
};

TEST_F(RulesEntryTest, InheritancePrintsNotImplemented) {
    EXPECT_NO_THROW({ rulesEntry(Functionality::Inheritance); });
    EXPECT_EQ(buffer.str(), "Inheritance rules not implemented yet.\n");
}

TEST_F(RulesEntryTest, OtherFunctionalityPrintsNothing) {
    EXPECT_NO_THROW({ rulesEntry(Functionality::DummyExamples); });
    EXPECT_EQ(buffer.str(), "");
}
