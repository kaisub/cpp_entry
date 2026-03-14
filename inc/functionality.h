#pragma once

enum class Functionality {
    DummyExamples = 0,
    ClassArrays,
    ClassInheritance,
    ClassMoveable,
    SmartPointers,
    DummyAlgorithm, //FIXME just a placeholder
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
    case Functionality::SmartPointers:
        return FunctionalityType::Rules;

    case Functionality::DummyAlgorithm:
        return FunctionalityType::Algorithms;

    default:
        return FunctionalityType::None;
    };
}
