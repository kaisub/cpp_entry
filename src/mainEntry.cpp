#include <iostream>
#include <magic_enum.hpp>
#include <string>

#include "mainEntry.h"

using std::cout;

std::vector<Functionality> parseArguments(std::span<const char*> args)
{
    // no arguments? Run all functionality
    if (args.size() <= 1) {
        auto values = magic_enum::enum_values<Functionality>();
        return std::vector<Functionality>{values.begin(), values.end()};
    }

    std::vector<Functionality> arguments;
    arguments.reserve(args.size() - 1);
    for (std::size_t i = 1; i < args.size(); ++i) {
        const int value = std::stoi(args[i]);
        // Validate that the parsed integer corresponds to a known Functionality
        auto enum_value = magic_enum::enum_cast<Functionality>(value);
        if (enum_value.has_value()) {
            arguments.push_back(enum_value.value());
        } else {
            throw std::invalid_argument("Invalid Functionality value provided: " + std::string(args[i]));
        }
    }
    return arguments;
}

void callProjectFunctionality(std::span<const Functionality> args, IFunctionalityDispatcher& dispatcher)
{
    for (const auto &arg : args)
    {
        cout << "Processing argument: " << static_cast<int>(arg) << '\n';
        switch (arg)
        {
        case Functionality::DummyExamples:
            dispatcher.onDummyEntry();
            break;
            
        case Functionality::Inheritance:
            dispatcher.onRulesEntry(arg);
            break;
        }
    }
}
