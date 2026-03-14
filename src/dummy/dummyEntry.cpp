#include <iostream>

#include "dummy/dummyDataProcessor.h"
#include "dummy/dummyEntry.h"
#include "dummy/dummyFunc.h"

constexpr const char *dummy_func_message = "hello from func\n";

using std::cout;

void dummyEntry() {
    cout << "\nThis is the dummy entry point.\n\n";
    dummyFunc(dummy_func_message);

    DummyDataProcessor processor;
    processor.add_value(10);
    cout << "Size: " << processor.get_size() << '\n';

    processor.clear_data();
    cout << "Size after clearing: " << processor.get_size() << '\n';
}
