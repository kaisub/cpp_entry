#include <iostream>
#include <exception>
#include <cstdio> // Required for std::printf

#include "dummy/dummyFunc.h"

int main(int argc, const char* argv[]) // NOLINT(modernize-use-trailing-return-type)
{
    try
    {
        callDummyExamples();
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
