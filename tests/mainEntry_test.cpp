#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <functional>
#include <magic_enum.hpp>
#include <span>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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
    MOCK_METHOD(void, onAlgorithmsEntry, (Functionality), (override));
};

// Helper template to avoid boilerplate code for dispatcher tests
template <typename SetupExpectationFunc>
void verifyDispatcherCall(Functionality func, SetupExpectationFunc setupExpectation)
{
    MockFunctionalityDispatcher mock;
    setupExpectation(mock);
    callProjectFunctionality(std::vector<Functionality>{ func }, mock);
}

// --- Types & Test Fixture ---
// Structure holding the enum value and its expected mock behavior
struct DispatcherTestParam {
    Functionality func;
    std::function<void(MockFunctionalityDispatcher&)> setupMock;
};

// Parameterized test fixture
class CallProjectFunctionalityTest : public testing::TestWithParam<DispatcherTestParam> {};

// --- The Core Test ---
TEST_P(CallProjectFunctionalityTest, RoutesToCorrectMethod) {
    auto param = GetParam();
    verifyDispatcherCall(param.func, param.setupMock);
}

// --- Mock Setup Helpers ---
auto expectOnDummyEntry = []() {
    return [](MockFunctionalityDispatcher& mock) {
        EXPECT_CALL(mock, onDummyEntry()).Times(1);
    };
};

auto expectRulesEntry = [](Functionality f)
{
    return [f](MockFunctionalityDispatcher &mock)
    {
        EXPECT_CALL(mock, onRulesEntry(f)).Times(1);
    };
};

auto expectAlgorithmsEntry = [](Functionality f)
{
    return [f](MockFunctionalityDispatcher &mock)
    {
        EXPECT_CALL(mock, onAlgorithmsEntry(f)).Times(1);
    };
};

// --- Test Data Generation ---
// Automatically generates test parameters for all enum values using magic_enum
std::vector<DispatcherTestParam> generateDispatcherTestParams()
{
    std::vector<DispatcherTestParam> params;

    // Iterate over all values defined in the Functionality enum
    for (auto funct : magic_enum::enum_values<Functionality>())
    {
        switch (functionalityIsOfType(funct)) {
        case FunctionalityType::Dummy:
            params.push_back({funct, expectOnDummyEntry()});
            break;

        case FunctionalityType::Rules:
            params.push_back({funct, expectRulesEntry(funct)});
            break;

        case FunctionalityType::Algorithms:
            params.push_back({funct, expectAlgorithmsEntry(funct)});
            break;

        case FunctionalityType::None:
            break;
        }
    }
    return params;
}

// Custom name formatter to display the enum name in the console (e.g., ".../SmartPointers")
auto name_formatter = [](const auto& info) {
    return std::string(magic_enum::enum_name(info.param.func));
};

// --- Test Suite Instantiation ---
INSTANTIATE_TEST_SUITE_P(
    AllRoutes,
    CallProjectFunctionalityTest,
    testing::ValuesIn(generateDispatcherTestParams()),
    name_formatter
);

// Test: Unknown enum value (i.e. from casting) will not cause any dispatcher calls
TEST(CallProjectFunctionalityTest, IgnoresUnknownFunctionality) {
    MockFunctionalityDispatcher mock;
    
    // Fake enum by casting an out-of-range integer to Functionality
    std::vector<Functionality> args = { static_cast<Functionality>(999) };

    // Expectation: none of the dispatcher methods should be called for unknown functionality
    EXPECT_CALL(mock, onDummyEntry()).Times(0);
    EXPECT_CALL(mock, onRulesEntry(testing::_)).Times(0);
    EXPECT_CALL(mock, onAlgorithmsEntry(testing::_)).Times(0);

    // Act & Assert: Function should handle unknown functionality gracefully without throwing exceptions
    EXPECT_NO_THROW({ callProjectFunctionality(args, mock); });
}
