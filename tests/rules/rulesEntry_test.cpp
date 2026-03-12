#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <sstream>
#include <string>
#include <magic_enum.hpp>
#include <vector>
#include <algorithm>

#include "rules/rulesEntry.h"
#include "functionality.h"

using testing::HasSubstr;
using testing::Not;

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

const std::vector<Functionality> handled_cases = {
    Functionality::ClassInheritance,
    Functionality::ClassMoveable,
    Functionality::SmartPointers
};

// get functionalities that are not in handled_cases
std::vector<Functionality> GetUnhandledFunctionalities() {
    std::vector<Functionality> unhandled;
    for (auto func : magic_enum::enum_values<Functionality>()) {
        if (std::find(handled_cases.begin(), handled_cases.end(), func) == handled_cases.end()) {
            unhandled.push_back(func);
        }
    }
    return unhandled;
}

// Custom name formatter to display the enum name in the console (e.g., ".../SmartPointers")
auto funcPrinter = [](const testing::TestParamInfo<Functionality>& info) {
    return std::string(magic_enum::enum_name(info.param));
};

// Test for handled Functionality enums
class RulesEntryHandledTest : public RulesEntryTest,
                              public testing::WithParamInterface<Functionality> {};

TEST_P(RulesEntryHandledTest, ExecutesWithoutUnhandledMessage) {
    EXPECT_NO_THROW({ rulesEntry(GetParam()); });
    // Verify that we do NOT hit the default case
    EXPECT_THAT(buffer.str(), Not(HasSubstr("unhandled functionality")));
}

INSTANTIATE_TEST_SUITE_P(
    HandledCases,
    RulesEntryHandledTest,
    testing::ValuesIn(handled_cases),
    funcPrinter);

// Test for NOT handled Functionality enums
class RulesEntryUnhandledTest : public RulesEntryTest,
                                public testing::WithParamInterface<Functionality>
{
};

TEST_P(RulesEntryUnhandledTest, PrintsUnhandledMessage)
{
    EXPECT_NO_THROW({ rulesEntry(GetParam()); });
    // Verify that we DO hit the default case with correct ID
    std::string expected = "unhandled functionality: " + std::to_string(static_cast<int>(GetParam())) + "\n";
    EXPECT_EQ(buffer.str(), expected);
}

INSTANTIATE_TEST_SUITE_P(
    UnhandledCases,
    RulesEntryUnhandledTest,
    testing::ValuesIn(GetUnhandledFunctionalities()),
    funcPrinter);
