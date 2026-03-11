#include <gtest/gtest.h>

#include "dummy/dummyEntry.h"

TEST(DummyTest, dummyEntryDoesNotCrash) {
    // Verify function can be called without crashing
    dummyEntry();
    SUCCEED();
}
