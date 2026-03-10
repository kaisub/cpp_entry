#include <iostream>
#include <exception>
#include <cstdio> // Required for std::printf

#include "dummy/dummyFunc.h"
#include "dummy/dummy_data_processor.h"

constexpr const char* dummy_func_message = "hello from func\n";

int main(int argc, const char* argv[]) // NOLINT(modernize-use-trailing-return-type)
{
    try
    {
        dummyFunc(dummy_func_message);

        DummyDataProcessor processor;
        processor.add_value(10);
        std::cout << "Size: " << processor.get_size() << '\n';
        
        processor.clear_data();
        std::cout << "Size after clearing: " << processor.get_size() << '\n';
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
