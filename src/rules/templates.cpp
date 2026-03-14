#include "rules/templates.h"
#include <iostream>
#include <format>
#include <span>

using std::cout;

#ifdef _MSC_VER
    #define PROJECT_FUNCTION_NAME __FUNCSIG__
#else
    #define PROJECT_FUNCTION_NAME __PRETTY_FUNCTION__
#endif

template<typename... T>
void printArgs(const T&... args)
{
    ((cout << args << " "), ...);
    cout << '\n';
}

template <int SIZE>
void printArray(const int (&arr)[SIZE]) //NOLINT(modernize-avoid-c-arrays)
{
    for (int i = 0; i < SIZE; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << '\n';
}

template <int x, int y>
void zeroArray(int (&arr)[x][y]) //NOLINT(modernize-avoid-c-arrays)
{
    for (int i = 0; i < x; ++i)
    {
        for (int j = 0; j < y; ++j)
        {
            arr[i][j] = 0;
        }
    }
}

template<typename... Args>
void printWithPrefix(std::string_view prefix, Args... args) {
    // 1. Print the prefix
    std::cout << prefix;

    // 2. -> Use a lambda to handle the spaces with fold expresionsion
    // ( ([v = std::forward<Args>(args)] {
    //     std::cout << " ";
    //     std::cout << v;
    // }()), ... );
    std::cout << '\n';
    // 3. -> Use a fold expression to print spaces between arguments
    ((std::cout << " " << std::forward<Args>(args)), ...);
    std::cout << '\n';
}

template <typename T>
constexpr std::string_view getTypeName()
{
    const std::string_view name = PROJECT_FUNCTION_NAME;
    const std::string_view prefix = "T = ";

    size_t start = name.find(prefix);
    if (start == std::string_view::npos) { return "unknown"; }
    start += prefix.size();

    size_t end = name.find_first_of(";]", start);
    
    return name.substr(start, end - start);
}

void printTypeNames()
{
    // auto x = {{5}};
    auto valx{5};      // auto -> int
    auto valy = {5};   // auto -> initialization_list of int
    // print type id
    cout << "x " << valx << " type: " << typeid(valx).name() << " y = {5} " << typeid(valy).name() << '\n';
    // good printing of type
    std::span svaly{valy};
    cout << "y " << svaly[0] << " type: " << getTypeName<decltype(valy)>() << " y={5} " << getTypeName<decltype(valy)>() << "\n";
}

void demonstrateTempates()
{
    cout << "*** printTemplates() ***" << '\n';

    printArgs(1, 2.5, "Hello", 'A');

    int arr[] = {1, 2, 3, 4, 5}; //NOLINT(modernize-avoid-c-arrays)
    printArray(arr);

    int arr2[2][3] = {{1, 2, 3}, {4, 5, 6}}; //NOLINT(modernize-avoid-c-arrays)
    cout << std::format("2D array size: {}\n", sizeof(arr2) / sizeof(arr2[0][0]));
    printArray(arr2[0]);
    printArray(arr2[1]);
    zeroArray(arr2);
    printArray(arr2[0]);
    printArray(arr2[1]);

    printWithPrefix("Value:", 1, 2.5, "Hello", 'A');

    printTypeNames();

    cout << '\n';
}
