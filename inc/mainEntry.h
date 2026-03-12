#pragma once

#include <span>

#include "functionalityDispatcher.h"

inline FunctionalityDispatcher globalDispatcher;

// Parses command-line arguments into a list of Functionality enums
std::vector<Functionality> parseArguments(std::span<const char *> args);

void callProjectFunctionality(
    std::span<const Functionality> args = {},
    IFunctionalityDispatcher &dispatcher = globalDispatcher);
