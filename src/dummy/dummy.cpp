#include <iostream>

#include "dummy/dummyFunc.h"
#include "dummy/dummy_data_processor.h"

constexpr const char *dummy_func_message = "hello from func\n";

void callDummyExamples()
{
    dummyFunc(dummy_func_message);

    DummyDataProcessor processor;
    processor.add_value(10);
    std::cout << "Size: " << processor.get_size() << '\n';

    processor.clear_data();
    std::cout << "Size after clearing: " << processor.get_size() << '\n';
}
