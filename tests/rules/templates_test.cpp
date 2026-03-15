#include "stdafx.h"
#include "rules/templates.h"

using testing::HasSubstr;

class TemplatesTest : public ::testing::Test {
protected:
    static std::string output;

    // SetUpTestSuite() is called once before all tests in this fixture
    static void SetUpTestSuite() {
        if (output.empty()) {
            output = captureCout([]() {
                demonstrateTempates();
            });
        }
    }
};

// Initialize the static member
std::string TemplatesTest::output;

TEST_F(TemplatesTest, DemonstrateTemplatesOutputsHeader) {
    EXPECT_THAT(output, HasSubstr("*** printTemplates() ***"));
}

TEST_F(TemplatesTest, PrintArgsVariadicOutput) {
    // printArgs(1, 2.5, "Hello", 'A')
    EXPECT_THAT(output, HasSubstr("1 2.5 Hello A"));
}

TEST_F(TemplatesTest, PrintArrayOutput) {
    // printArray({1,2,3,4,5})
    EXPECT_THAT(output, HasSubstr("1 2 3 4 5"));
}

TEST_F(TemplatesTest, TwoDArraySizeOutput) {
    EXPECT_THAT(output, HasSubstr("2D array size: 6"));
}

TEST_F(TemplatesTest, TwoDArrayRowsOutput) {
    // rows before zeroing
    EXPECT_THAT(output, HasSubstr("1 2 3"));
    EXPECT_THAT(output, HasSubstr("4 5 6"));
}

TEST_F(TemplatesTest, ZerArrayZeroesOutput) {
    // after zerArray, both rows print "0 0 0"
    EXPECT_THAT(output, HasSubstr("0 0 0"));
}

TEST_F(TemplatesTest, PrintWithPrefixOutput) {
    // printWithPrefix("Value:", 1, 2.5, "Hello", 'A')
    EXPECT_THAT(output, HasSubstr("Value:\n 1 2.5 Hello A"));
}

TEST_F(TemplatesTest, PrintTypeNamesOutput) {
    // printTypeNames()
    EXPECT_THAT(output, HasSubstr("x 5 type:"));
    EXPECT_THAT(output, HasSubstr("y={5}"));
}
