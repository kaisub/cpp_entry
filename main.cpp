#include <iostream>
#include <exception>
#include <cstdio> // Required for std::printf
#include <vector>
#include <string>

#include "mainEntry.h"
#include <optional>

using std::cout;

constexpr std::optional<Functionality> expected_func = std::nullopt; // Set to a specific Functionality value for local testing, or leave as nullopt to parse from command line arguments.

int main(int argc, const char* argv[]) // NOLINT(modernize-use-trailing-return-type)
{
    try
    {
        // for local development and testing, we can hardcode the functionality to run given Functionality only
        if (!expected_func) {
            callProjectFunctionality(parseArguments(std::span<const char*>(argv, argc)));
        }
        else {
            callProjectFunctionality(std::vector<Functionality>{expected_func.value()});
        }
    }
    catch(const std::exception& e)
    {
        // std::printf does not throw C++ exceptions, making it 100% safe here
        std::printf("Exception caught: %s\n", e.what());
        return 1;
    }
    catch (...) 
    {
        // Catch-all for any other unknown exceptions
        std::printf("Unknown fatal error occurred.\n");
        return 1;
    }
    
    return 0;
}
