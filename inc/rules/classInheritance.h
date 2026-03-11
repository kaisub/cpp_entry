#pragma once

// Demonstrates multiple inheritance and abstract interfaces in C++

void demonstrateClassInheritance();

class Base {
public:
    explicit Base(int val = 0);
    virtual ~Base();

    virtual void print() const;

protected:
    int val;
};

class AbstractInterfaceOne {
public:
    virtual ~AbstractInterfaceOne();

    virtual void interfacePrintOne() const = 0;
};

class AbstractInterfaceTwo {
public:
    virtual ~AbstractInterfaceTwo();

    virtual void interfacePrintTwo() const = 0;
};

class AA final : public Base, public AbstractInterfaceOne, public AbstractInterfaceTwo {
public:
    AA(int valX, int valY, int valA = 0);
    ~AA() override;

    void interfacePrintOne() const override;

    void interfacePrintTwo() const override;

    void print() const override;

private:
    int valX;
    int valY;
};
