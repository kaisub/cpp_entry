#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "mainEntry.h"

// Test: No args (argc <= 1) should return all functionalities
TEST(ParseArgumentsTest, NoArgumentsReturnsAll)
{
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

// Test: Valid argument (0) should return Functionality::DummyExamples
TEST(ParseArgumentsTest, ValidArgumentReturnsFunctionality)
{
    const auto arg = std::to_string(static_cast<int>(Functionality::DummyExamples));
    const char* argv[] = { "app_name", arg.c_str() };
    int argc = 2;

    auto result = parseArguments(std::span<const char*>(argv, argc));

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], Functionality::DummyExamples);
}

// Test: Argument out of bounds for enum should throw exception
TEST(ParseArgumentsTest, InvalidIntegerThrows) {
    const char* argv[] = { "app_name", "999" };
    int argc = 2;

    EXPECT_THROW(parseArguments(std::span<const char*>(argv, argc)), std::invalid_argument);
}

// Test: Argument not being a number should throw exception
TEST(ParseArgumentsTest, NonIntegerThrows) {
    const char* argv[] = { "app_name", "abc" };
    int argc = 2;

    EXPECT_THROW(parseArguments(std::span<const char*>(argv, argc)), std::invalid_argument);
}
