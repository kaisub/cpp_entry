#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <sstream>
#include <string>

#include "rules/classInheritance.h"

// Helper function to capture both std::cout and std::puts (C-style stdout)
std::string captureCout(std::function<void()> func) {
    // Start capturing standard output at the OS level
    testing::internal::CaptureStdout();
    
    // Execute the user's function
    func();
    
    // Force flush both C++ and C streams to ensure all output is captured
    std::cout.flush();
    std::fflush(stdout);
    
    // Stop capturing and return the accumulated string
    return testing::internal::GetCapturedStdout();
}

TEST(BaseTest, PrintOutputsCorrectly) {
    Base base(42);
    std::string output = captureCout([&]() { base.print(); });
    EXPECT_THAT(output, testing::HasSubstr("Base::print() a = 42"));
}

TEST(BaseTest, DestructorOutputsCorrectly) {
    std::string output = captureCout([&]() {
        Base base(42);
    });
    EXPECT_THAT(output, testing::HasSubstr("~Base::destructor"));
}

TEST(AbstractInterfaceOneTest, CannotInstantiateAbstract) {
    // AbstractInterfaceOne is abstract, no test needed, but to show it's abstract.
    EXPECT_FALSE(std::is_constructible<AbstractInterfaceOne>::value);}

TEST(AbstractInterfaceTwoTest, CannotInstantiateAbstract) {
    // AbstractInterfaceTwo is abstract, no test needed, but to show it's abstract.
    EXPECT_FALSE(std::is_constructible<AbstractInterfaceTwo>::value);
}

TEST(AATest, PrintOutputsCorrectly) {
    AA aa(10, 20, 30);
    std::string output = captureCout([&]() { aa.print(); });
    EXPECT_THAT(output, testing::HasSubstr("*** AA::print() ***"));
    EXPECT_THAT(output, testing::HasSubstr("Base::print() a = 30"));
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintOne() called"));
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintTwo() called"));
    EXPECT_THAT(output, testing::HasSubstr("x: 10 y: 20 a: 30"));
}

TEST(AATest, InterfacePrintOneOutputsCorrectly) {
    AA aa(1, 2, 3);
    std::string output = captureCout([&]() { aa.interfacePrintOne(); });
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintOne() called"));
}

TEST(AATest, InterfacePrintTwoOutputsCorrectly) {
    AA aa(1, 2, 3);
    std::string output = captureCout([&]() { aa.interfacePrintTwo(); });
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintTwo() called"));
}

TEST(AATest, DestructorOutputsCorrectly) {
    std::string output = captureCout([&]() {
        AA aa(1, 2, 3);
    });
    EXPECT_THAT(output, testing::HasSubstr("~AA::destructor"));
    EXPECT_THAT(output, testing::HasSubstr("~Base::destructor"));
    // Note: Abstract interfaces destructors also called, but since they are virtual, order might vary.
}

TEST(PolymorphismTest, BasePointerToAA) {
    std::unique_ptr<Base> ptr = std::make_unique<AA>(1, 2, 3);
    std::string output = captureCout([&]() { ptr->print(); });
    EXPECT_THAT(output, testing::HasSubstr("*** AA::print() ***"));
    EXPECT_THAT(output, testing::HasSubstr("Base::print() a = 3"));
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintOne() called"));
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintTwo() called"));
    EXPECT_THAT(output, testing::HasSubstr("x: 1 y: 2 a: 3"));
}

TEST(PolymorphismTest, AbstractInterfaceOnePointerToAA) {
    std::unique_ptr<AbstractInterfaceOne> ptr = std::make_unique<AA>(1, 2, 3);
    std::string output = captureCout([&]() { ptr->interfacePrintOne(); });
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintOne() called"));
}

TEST(PolymorphismTest, AbstractInterfaceTwoPointerToAA) {
    std::unique_ptr<AbstractInterfaceTwo> ptr = std::make_unique<AA>(1, 2, 3);
    std::string output = captureCout([&]() { ptr->interfacePrintTwo(); });
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintTwo() called"));
}

TEST(MultipleInheritanceTest, AAInheritsFromAll) {
    AA aa(1, 2, 3);
    // Test that it can be cast to base classes
    Base* basePtr = &aa;
    AbstractInterfaceOne* iface1Ptr = &aa;
    AbstractInterfaceTwo* iface2Ptr = &aa;
    EXPECT_NE(basePtr, nullptr);
    EXPECT_NE(iface1Ptr, nullptr);
    EXPECT_NE(iface2Ptr, nullptr);
}

TEST(DemonstrateClassInheritanceTest, ExecutesAndPrintsExpectedOutput) {
    std::string output = captureCout([&]() {
        demonstrateClassInheritance();
    });

    EXPECT_THAT(output, testing::HasSubstr("Demonstrating class inheritance"));
    EXPECT_THAT(output, testing::HasSubstr("*** AA::print() ***"));
    EXPECT_THAT(output, testing::HasSubstr("Base::print()"));
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintOne() called"));
    EXPECT_THAT(output, testing::HasSubstr("AA::interfacePrintTwo() called"));
}
