#pragma once

#include <span>

enum class Functionality {
    DummyExamples = 0,
    // Add more functionalities here as needed
};

std::vector<Functionality> parseArguments(std::span<const char*> args);

void callProjectFunctionality(std::span<const Functionality> args = {});
