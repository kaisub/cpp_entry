#pragma once

#include "stdafx.h"
#include "functionality.h"

// Base test fixture for redirecting std::cout
class CoutRedirectTest : public ::testing::Test {
protected:
    std::stringstream buffer;
    std::streambuf* old_cout_buffer = nullptr;

    void SetUp() override {
        old_cout_buffer = std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(old_cout_buffer);
    }
};

// Gets functionalities that are not in the handled_cases list
inline std::vector<Functionality> GetUnhandledFunctionalities(const std::vector<Functionality>& handled_cases) {
    std::vector<Functionality> unhandled;
    for (auto func : magic_enum::enum_values<Functionality>()) {
        if (std::find(handled_cases.begin(), handled_cases.end(), func) == handled_cases.end()) {
            unhandled.push_back(func);
        }
    }
    return unhandled;
}

// Custom name formatter to display the enum name in the console
inline std::string funcPrinter(const testing::TestParamInfo<Functionality>& info) {
    return std::string(magic_enum::enum_name(info.param));
}
