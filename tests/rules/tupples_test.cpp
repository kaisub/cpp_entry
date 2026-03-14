#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "rules/tupples.h"
#include "common/common.h"

using testing::HasSubstr;

TEST(TupplesTest, DemonstrateTupplesOutputsExpectedStrings) {
    std::string output = captureCout([]() {
        demonstrateTupples();
    });

    EXPECT_THAT(output, HasSubstr("*** printTuples ***"));
    EXPECT_THAT(output, HasSubstr("tupleOne: size 3 (5, 7.3, Welcome)"));
    EXPECT_THAT(output, HasSubstr("tupleTwo elements: 42 3.14 Hello"));
    EXPECT_THAT(output, HasSubstr("Structured Binding: i=42, d=3.14, s=Hello"));
    EXPECT_THAT(output, HasSubstr("Extracted using tie: number=42, hello=Hello"));
}
