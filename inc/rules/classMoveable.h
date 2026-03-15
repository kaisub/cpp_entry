#pragma once

#include <string>

void demonstrateClassMoveable();

class Movable {
private:
    int *data = nullptr;
    std::string name = {};

public:
    explicit Movable(int value = 0);
    explicit Movable(std::string name);

    ~Movable();

    Movable(const Movable &other);
    Movable(Movable &&other) noexcept;

    operator const std::string &() const;

    // NO copy operator
    Movable &operator=(const Movable &other) = delete;
    // NO move operator
    Movable &operator=(Movable &&other) = delete;
};
