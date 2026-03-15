#pragma once

#include <memory>
#include <string>

void demonstrateClassMoveable();

class Movable {
private:
    std::unique_ptr<int> data = nullptr;
    std::string name = {};

public:
    explicit Movable(int value = 0);
    explicit Movable(std::string name);

    ~Movable() = default;

    Movable(const Movable &other);
    Movable(Movable &&other) noexcept;

    operator const std::string &() const;

    // NO copy operator
    Movable &operator=(const Movable &other) = delete;
    // NO move operator
    Movable &operator=(Movable &&other) = delete;
};
