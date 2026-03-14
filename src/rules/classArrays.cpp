#include "rules/classArrays.h"

#include <algorithm>
#include <cstdio> // Required for std::puts
#include <format>
#include <iostream>
#include <string>
#include <utility> // Required for std::swap


using std::cout;

template<typename T>
MyContainer<T>::MyContainer(std::initializer_list<T> val) : data_buffer(val)
{
}

template<typename T>
MyContainer<T>::MyContainer(const MyContainer& other) : id(other.id), data_buffer(other.data_buffer) {
    cout << "Copy for id: " << id << '\n';
}

template<typename T>
MyContainer<T>& MyContainer<T>::operator=(const MyContainer& other)
{
    if (this != &other) { // Protect against self-assignment
        cout << "Copy Assignment for id: " << id << " (target) from " << other.id << " (source)\n";
        id = other.id;
        data_buffer = other.data_buffer;
    }
    return *this;
}

template<typename T>
MyContainer<T>::MyContainer(MyContainer&& other) noexcept : id(other.id), data_buffer(std::move(other.data_buffer))
{
    std::printf("Move for id: %d\n", id);
}

template<typename T>
MyContainer<T>& MyContainer<T>::operator=(MyContainer&& other) noexcept
{
   if (this != &other) {
        std::printf("Assignment for id: %d\n", id);
        id = other.id;
        std::swap(data_buffer, other.data_buffer);    // Swap the contents
    }
    return *this;
}

template<typename T>
void MyContainer<T>::print() const
{
    cout << "MyContainer id: " << id << " no:" << global_call_count++ << " has: ";
    std::for_each(data_buffer.begin(), data_buffer.end(), [](const T& elem) {
        cout << elem << " ";
    });
    cout << '\n';
}

template class MyContainer<int>;
template class MyContainer<std::string>;

void printMyContainer()
{
    MyContainer<int> poj({2,3,4,5});
    poj.print();
    MyContainer<std::string> poj_str({"Hello", "World", "C++"});
    poj_str.print();
    MyContainer<std::string> poj_str2 = std::move(poj_str);
    poj_str2.print();
    poj_str = std::move(poj_str2);
    poj_str.print();

    MyContainer<std::string> poj_str3 = poj_str; // Copy constructor
    poj_str3.print();
    MyContainer<std::string> poj_str4{}; // Default constructor
    poj_str4 = poj_str; // Copy assignment
    poj_str4.print();

    cout << "\n\n";
}

void printContainers()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
    cout << std::format("Size: {} First: {}\n", vec.size(), vec[0]);

    int arr_one[] = {10, 20, 30, 40, 50, 60}; //NOLINT(modernize-avoid-c-arrays)
    cout << std::format("arrOne size: {} First: {}\n", std::size(arr_one), arr_one[0]);
    for (int elem : arr_one) {
        cout << elem << " ";
    }
    cout << '\n';
    
    int arr_two[5] = {51, 52, 53}; //NOLINT(modernize-avoid-c-arrays)
    cout << std::format("arrTwo size: {} First: {}\n", std::size(arr_two), arr_two[0]);
    for (int elem : arr_two) {
        cout << elem << " ";
    }
    cout << '\n';
    std::ranges::for_each(std::begin(arr_two), std::end(arr_two), [](int elem) {
        cout << elem << " ";
    });
    cout << "\n\n";
}

void demonstrateClassArrays()
{
    cout << "*** printArrays ***" << '\n';

    printContainers();

    printMyContainer();
}
