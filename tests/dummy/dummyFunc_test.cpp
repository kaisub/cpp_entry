#include <gtest/gtest.h>

#include "dummy/dummyFunc.h"

constexpr const char* dummy_func_message = "hello from func\n";

TEST(DummyTest, DummyFuncPrintsCorrectMessage) {
    // 1. Redirect cout to a stringstream
    std::stringstream buffer;
    std::streambuf* old_cout_buffer = std::cout.rdbuf(buffer.rdbuf());

    // 2. Call the function that prints to cout
    dummyFunc(dummy_func_message);

    // 3. Restore the original cout buffer (crucial to avoid crashes!)
    std::cout.rdbuf(old_cout_buffer);

    // 4. Verify the output stored in the buffer
    EXPECT_EQ(buffer.str(), dummy_func_message);
}
