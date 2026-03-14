#pragma once

#include <vector>
#include <initializer_list>

void demonstrateClassArrays();

template <typename T>
class MyContainer {
    static inline int global_call_count = 0;

    int id = []() {
        static int counter = 0; 
        return counter++;
    }();
    std::vector<T> data_buffer;

public:
    explicit MyContainer(std::initializer_list<T> val);

    ~MyContainer() = default;

    // Rule of Five
    MyContainer(const MyContainer& other);
    MyContainer& operator=(const MyContainer& other);

    MyContainer(MyContainer&& other) noexcept;
    MyContainer& operator=(MyContainer&& other) noexcept;
   
    void print() const;
};