#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <string>
#include <utility>

#include "rules/classMoveable.h"
#include "common/common.h"

using testing::HasSubstr;

TEST(MovableTest, IntConstructorAndGetValue) {
    int value = 0;
    std::string output = captureCout([&]() {
        Movable m(10);
        value = m.getValue();
    });
    EXPECT_EQ(value, 10);
    EXPECT_THAT(output, HasSubstr("Movable construct: 10"));
}

TEST(MovableTest, StringConstructorAndConversion) {
    int value = -1;
    std::string strVal;
    std::string output = captureCout([&]() {
        Movable m("test_string");
        value = m.getValue();
        
        // Test implicit/explicit conversion to string
        strVal = static_cast<std::string>(m);
    });
    EXPECT_EQ(value, 0);
    EXPECT_EQ(strVal, "test_string");
    EXPECT_THAT(output, HasSubstr("Movable construct with name: test_string"));
    EXPECT_THAT(output, HasSubstr("->Movable operator const std::string&: test_string<-"));
}

TEST(MovableTest, CopyConstructor) {
    int valCopy = -1;
    int valOrig = -1;
    std::string output = captureCout([&]() {
        Movable original(99);
        Movable copy(original);
        valCopy = copy.getValue();
        valOrig = original.getValue();
    });
    EXPECT_EQ(valCopy, 99);
    EXPECT_EQ(valOrig, 99); // Original still valid
    EXPECT_THAT(output, HasSubstr("Movable copy construct: 99"));
}

TEST(MovableTest, MoveConstructor) {
    int valMoved = -1;
    int valOrig = -1;
    std::string output = captureCout([&]() {
        Movable original(55);
        Movable moved(std::move(original));
        valMoved = moved.getValue();
        valOrig = original.getValue();
    });
    EXPECT_EQ(valMoved, 55);
    EXPECT_EQ(valOrig, 0); // Original data stolen/nulled
    // EXPECT_THAT(output, HasSubstr("Movable move construct: 55"));
}

TEST(MovableTest, DemonstrateClassMoveableIntegration) {
    std::string output = captureCout([]() {
        demonstrateClassMoveable();
    });

    EXPECT_THAT(output, HasSubstr("*** printMove ***"));
    EXPECT_THAT(output, HasSubstr("Movable construct: 42"));
    EXPECT_THAT(output, HasSubstr("Movable copy construct: 42"));
    // EXPECT_THAT(output, HasSubstr("Movable move construct: 42"));
    EXPECT_THAT(output, HasSubstr("fun taking const ref: 100"));
    EXPECT_THAT(output, HasSubstr("fun taking rvalue ref: 200"));
    EXPECT_THAT(output, HasSubstr("mo7 name: ->Movable operator const std::string&: mo7<- mo7"));
}
