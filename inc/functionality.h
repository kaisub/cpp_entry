#pragma once

enum class Functionality {
    DummyExamples = 0,
    ClassArrays,
    ClassInheritance,
    ClassMoveable,
    Lambdas,
    SmartPointers,
    Templates,
    Tupples,
    PrintDir,
};

enum class FunctionalityType {
    Dummy = 0,
    Rules,
    Algorithms,
    None
};

[[nodiscard]] inline FunctionalityType functionalityIsOfType(Functionality funct)
{
    switch(funct) {
    case Functionality::DummyExamples:
        return FunctionalityType::Dummy;

    case Functionality::ClassArrays:
    case Functionality::ClassInheritance:
    case Functionality::ClassMoveable:
    case Functionality::Lambdas:
    case Functionality::SmartPointers:
    case Functionality::Templates:
    case Functionality::Tupples:
        return FunctionalityType::Rules;

    case Functionality::PrintDir:
        return FunctionalityType::Algorithms;

    default:
        return FunctionalityType::None;
    };
}
