#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <span>
#include <magic_enum.hpp>

#include "mainEntry.h"

// Test: No args (argc <= 1) should return all functionalities
TEST(ParseArgumentsTest, NoArgumentsReturnsAll) {
    const char* argv[] = { "app_name" };
    int argc = 1;

    auto result = parseArguments(std::span<const char*>(argv, argc));

    ASSERT_FALSE(result.empty());
    
    // Check if the default functionality is in the list
    bool found = false;
    for (const auto& func : result) {
        if (func == Functionality::DummyExamples) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

// Test: Argument not being a number should throw exception
TEST(ParseArgumentsTest, NonIntegerThrows) {
    const char* argv[] = { "app_name", "abc" };
    int argc = 2;

    EXPECT_THROW(parseArguments(std::span<const char*>(argv, argc)), std::invalid_argument);
}

// Test: Valid argument (0) should return Functionality::DummyExamples
TEST(ParseArgumentsTest, ValidArgumentReturnsFunctionality) {
    const auto arg = std::to_string(static_cast<int>(Functionality::DummyExamples));
    const char* argv[] = { "app_name", arg.c_str() };
    int argc = 2;

    auto result = parseArguments(std::span<const char*>(argv, argc));

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], Functionality::DummyExamples);
}

// Test: All valid arguments explicitly provided should return all Functionalities
TEST(ParseArgumentsTest, AllExplicitArgumentsReturnAll) {
    // Retrieve all enum values automatically (1, 2, 3, ...)
    const auto all_values = magic_enum::enum_values<Functionality>();

    // Store strings in a vector to ensure memory validity for c_str() pointers
    std::vector<std::string> args_store;
    args_store.reserve(all_values.size() + 1);
    args_store.push_back("app_name");
    
    for (const auto& val : all_values) {
        args_store.push_back(std::to_string(static_cast<int>(val)));
    }

    // Create vector of pointers acting as argv
    std::vector<const char*> argv;
    for (const auto& s : args_store) {
        argv.push_back(s.c_str());
    }

    auto result = parseArguments(argv);

    ASSERT_EQ(result.size(), all_values.size());
    // Compare the result vector with the original enum values
    std::vector<Functionality> expected(all_values.begin(), all_values.end());
    EXPECT_EQ(result, expected);
}

// Test: Argument out of bounds for enum should throw exception
TEST(ParseArgumentsTest, InvalidIntegerThrows) {
    const char* argv[] = { "app_name", "9999" };
    int argc = 2;

    EXPECT_THROW(parseArguments(std::span<const char*>(argv, argc)), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// GMock Tests for FunctionalityDispatcher

class MockFunctionalityDispatcher : public IFunctionalityDispatcher {
public:
    MOCK_METHOD(void, onDummyEntry, (), (override));
    MOCK_METHOD(void, onRulesEntry, (Functionality), (override));
};

// Helper template to avoid boilerplate code for dispatcher tests
template <typename SetupExpectationFunc>
void verifyDispatcherCall(Functionality func, SetupExpectationFunc setupExpectation)
{
    MockFunctionalityDispatcher mock;
    std::vector<Functionality> args = { func };

    setupExpectation(mock);

    callProjectFunctionality(args, mock);
}

// Following tests corresponds to the functionalities defined in Functionality enum
// and their respective dispatcher methods in IFunctionalityDispatcher interface.
TEST(CallProjectFunctionalityTest, CallsDummyExamples) {
    verifyDispatcherCall(Functionality::DummyExamples, [](MockFunctionalityDispatcher& mock) {
        EXPECT_CALL(mock, onDummyEntry()).Times(1);
    });
}

TEST(CallProjectFunctionalityTest, CallsInheritance) {
    verifyDispatcherCall(Functionality::Inheritance, [](MockFunctionalityDispatcher& mock) {
        EXPECT_CALL(mock, onRulesEntry(Functionality::Inheritance)).Times(1);
    });
}

// Test: Unknown enum value (i.e. from casting) will not cause any dispatcher calls
TEST(CallProjectFunctionalityTest, IgnoresUnknownFunctionality) {
    MockFunctionalityDispatcher mock;
    
    // Fake enum by casting an out-of-range integer to Functionality
    std::vector<Functionality> args = { static_cast<Functionality>(999) };

    // Expectation: none of the dispatcher methods should be called for unknown functionality
    EXPECT_CALL(mock, onDummyEntry()).Times(0);
    EXPECT_CALL(mock, onRulesEntry(testing::_)).Times(0);

    // Act & Assert: Function should handle unknown functionality gracefully without throwing exceptions
    EXPECT_NO_THROW({ callProjectFunctionality(args, mock); });
}
