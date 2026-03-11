#include "dummy/dummyDataProcessor.h"

void DummyDataProcessor::add_value(int val)
{
    data.push_back(val);
}

void DummyDataProcessor::clear_data()
{
    data.clear();
}

size_t DummyDataProcessor::get_size() const
{
    return data.size();
}
