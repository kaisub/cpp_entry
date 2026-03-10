#include <gtest/gtest.h>

#include "dummy/dummy.h"

TEST(DummyTest, callDummyExamplesDoesNotCrash) {
    // Verify function can be called without crashing
    callDummyExamples();
    SUCCEED();
}
