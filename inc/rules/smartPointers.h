#pragma once

struct Simple
{
    static inline int counter = 0;
    int id = counter++;
    std::string name;
    explicit Simple(const char* name = "");
    ~Simple();
};

void pointersCreation();

void demonstrateSmartPointers();
