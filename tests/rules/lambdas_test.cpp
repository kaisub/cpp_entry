#include "stdafx.h"
#include "rules/lambdas.h"

using testing::HasSubstr;

TEST(LambdasTest, DemonstrateLambdasOutput) {
    std::string output = captureCout([]() {
        demonstrateLambdas();
    });

    // From Baz{"Hello"}.foo()
    EXPECT_THAT(output, HasSubstr("Hello"));
    // From Baz{"World"}.foo2()
    //EXPECT_THAT(output, HasSubstr("World"));
}
