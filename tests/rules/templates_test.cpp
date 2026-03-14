#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "rules/templates.h"
#include "common/common.h"

using testing::HasSubstr;

TEST(TemplatesTest, DemonstrateTemplatesOutputsHeader) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    EXPECT_THAT(output, HasSubstr("*** printTemplates() ***"));
}

TEST(TemplatesTest, PrintArgsVariadicOutput) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    // printArgs(1, 2.5, "Hello", 'A')
    EXPECT_THAT(output, HasSubstr("1 2.5 Hello A"));
}

TEST(TemplatesTest, PrintArrayOutput) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    // printArray({1,2,3,4,5})
    EXPECT_THAT(output, HasSubstr("1 2 3 4 5"));
}

TEST(TemplatesTest, TwoDArraySizeOutput) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    EXPECT_THAT(output, HasSubstr("2D array size: 6"));
}

TEST(TemplatesTest, TwoDArrayRowsOutput) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    // rows before zeroing
    EXPECT_THAT(output, HasSubstr("1 2 3"));
    EXPECT_THAT(output, HasSubstr("4 5 6"));
}

TEST(TemplatesTest, ZerArrayZeroesOutput) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    // after zerArray, both rows print "0 0 0"
    EXPECT_THAT(output, HasSubstr("0 0 0"));
}

TEST(TemplatesTest, PrintWithPrefixOutput) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    // printWithPrefix("Value:", 1, 2.5, "Hello", 'A')
    EXPECT_THAT(output, HasSubstr("Value:\n 1 2.5 Hello A"));
}

TEST(TemplatesTest, PrintTypeNamesOutput) {
    std::string output = captureCout([]() {
        demonstrateTempates();
    });
    // printTypeNames()
    EXPECT_THAT(output, HasSubstr("x 5 type:"));
    EXPECT_THAT(output, HasSubstr("y={5}"));
}
