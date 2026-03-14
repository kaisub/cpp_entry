#include "rules/tupples.h"
#include <iostream>
#include <format>
#include <tuple>

using std::cout;

void demonstrateTupples()
{
    cout << "*** printTuples ***\n";

    std::tuple<int, double, std::string> tuple_one(5, 7.3, "Welcome");
    std::cout << "tupleOne: size "
              << std::tuple_size_v<decltype(tuple_one)> << " ("
              << std::get<0>(tuple_one) << ", " 
              << std::get<1>(tuple_one) << ", " 
              << std::get<2>(tuple_one) << ")\n";

    auto tuple_two = std::make_tuple(42, 3.14, "Hello");
    std::apply([](auto&&... args) {
        cout << "tupleTwo elements: ";
        ((cout << args << " "), ...);
    }, tuple_two);
    cout << '\n';

    auto [val_i, val_d, val_s] = tuple_two; // Structured binding
    cout << "Structured Binding: i=" << val_i << ", d=" << val_d << ", s=" << val_s << '\n';
    cout << '\n';

    std::string hello;
    int number;
    std::tie(number, std::ignore, hello) = tuple_two;
    cout << std::format("Extracted using tie: number={}, hello={}\n", number, hello);

    cout << '\n';    
}
