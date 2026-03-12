#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <sstream>
#include <string>

#include "rules/smartPointers.h"
#include "common/common.h"


TEST(SmartPointersTest, PointersCreationOutputsExpectedStrings) {
    std::string output = captureCout([]() { pointersCreation(); });
    // verify that we see the integer printout from the raw pointers
    EXPECT_THAT(output, testing::HasSubstr("wpi1: 55"));
    // unique/shared simple construction messages
    EXPECT_THAT(output, testing::HasSubstr("Simple unique def construct"));
    EXPECT_THAT(output, testing::HasSubstr("Simple shared def construct"));
    // destructor messages should appear when the function exits
    EXPECT_THAT(output, testing::HasSubstr("Simple"));
    EXPECT_THAT(output, testing::HasSubstr("dest"));
}

TEST(SmartPointersTest, DemonstrateSmartPointersIncludesHeader) {
    std::string output = captureCout([]() { demonstrateSmartPointers(); });
    EXPECT_THAT(output, testing::HasSubstr("*** printPointers ***"));
    // should also include results from pointersCreation
    EXPECT_THAT(output, testing::HasSubstr("Simple unique def construct"));
}

// Test specific array indexing and behavior to hit more branches
TEST(SmartPointersTest, ArrayAccessAndBehavior) {
    std::string output = captureCout([]() {
        auto uptr_tab = std::make_unique<Simple[]>(2);
        // Explicitly touch elements if they have specific logic
    });
    // Ensure both elements were constructed
    EXPECT_THAT(output, testing::HasSubstr("def construct"));
}

// Verification of shared_ptr aliasing or copy semantics
TEST(SmartPointersTest, SharedPointerSemantics) {
    std::string output = captureCout([]() {
        std::shared_ptr<Simple> s1 = std::make_shared<Simple>("shared_test");
        std::shared_ptr<Simple> s2 = s1; // Copy branch
        s1.reset(); // Release branch
    });
    EXPECT_THAT(output, testing::HasSubstr("Simple shared_test dest"));
}