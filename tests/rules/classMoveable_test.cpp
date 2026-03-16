#include "stdafx.h"
#include "rules/classMoveable.h"

using testing::HasSubstr;

TEST(MovableTest, IntConstructor) {
    std::string output = captureCout([&]() {
        Movable m(10);
    });
    EXPECT_THAT(output, HasSubstr("Movable construct: 10"));
}

TEST(MovableTest, StringConstructorAndConversion) {
    std::string strVal;
    std::string output = captureCout([&]() {
        Movable m("test_string");
        
        // Test implicit/explicit conversion to string
        strVal = static_cast<std::string>(m);
    });
    EXPECT_EQ(strVal, "test_string");
    EXPECT_THAT(output, HasSubstr("Movable construct with name: test_string"));
    EXPECT_THAT(output, HasSubstr("->Movable operator const std::string&: test_string<-"));
}

TEST(MovableTest, CopyConstructor) {
    std::string output = captureCout([&]() {
        Movable original(99);
        Movable copy(original);
        // We can't access the value, but we can verify the constructors were called
        // and that destructors for both objects run without crashing (implicit test of deep copy).
    });
    EXPECT_THAT(output, HasSubstr("Movable construct: 99"));
    EXPECT_THAT(output, HasSubstr("Movable copy construct"));
}

TEST(MovableTest, MoveConstructor) {
    std::string output = captureCout([&]() {
        Movable original(55);
        Movable moved(std::move(original));
        // We can't access the value, but we can verify the move constructor was called
        // and that destructors for both objects run without crashing (implicit test of pointer move).
    });
    EXPECT_THAT(output, HasSubstr("Movable construct: 55"));
    EXPECT_THAT(output, HasSubstr("Movable move construct"));
}

TEST(MovableTest, DemonstrateClassMoveableIntegration) {
    std::string output = captureCout([]() {
        demonstrateClassMoveable();
    });

    EXPECT_THAT(output, HasSubstr("*** printMove ***"));
    EXPECT_THAT(output, HasSubstr("Movable construct: 42"));
    EXPECT_THAT(output, HasSubstr("Movable copy construct"));
    EXPECT_THAT(output, HasSubstr("Movable move construct"));
    EXPECT_THAT(output, HasSubstr("fun taking const ref: ")); // 100
    EXPECT_THAT(output, HasSubstr("fun taking rvalue ref: ")); // 200
    EXPECT_THAT(output, HasSubstr("mo7 name: ->Movable operator const std::string&: mo7<- mo7"));
}

TEST(MovableTest, CopyConstructorWithNullData) {
    std::string output = captureCout([&]() {
        // String constructor leaves 'data' as nullptr
        Movable original("null_data_test");

        // Copying it evaluates 'if (other.data != nullptr)' to false
        Movable copy(original);
    });

    EXPECT_THAT(output, HasSubstr("Movable construct with name: null_data_test"));
    EXPECT_THAT(output, HasSubstr("Movable copy construct"));
}
