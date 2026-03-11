#pragma once

#include <vector>

// DUMMY CLASS FOR TESTING PURPOSES
class DummyDataProcessor {
public:
    void add_value(int val);
    
    void clear_data();
    
    size_t get_size() const;

    std::vector<int> data;
};
