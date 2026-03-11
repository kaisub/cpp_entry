#include <gtest/gtest.h>

#include "dummy/dummyDataProcessor.h"

// -----------------------------------------------------------------------------
// TEST FIXTURE CLASS Must inherit from ::testing::Test.
// The name of this class will be the first argument in the TEST_F macro.

class DummyDataProcessorTest : public ::testing::Test
{
protected:
    DummyDataProcessor processor;

    // SetUp() is executed immediately BEFORE each test runs.
    void SetUp() override {
        processor.add_value(10);
        processor.add_value(20);
    }

    // TearDown() is executed immediately AFTER each test finishes.
    void TearDown() override {
        processor.clear_data();
    }
};

// -----------------------------------------------------------------------------
// TEST_F gives you direct access to the 'processor' object defined in the fixture.

TEST_F(DummyDataProcessorTest, InitialSizeIsCorrectAfterSetUp) {
    // We expect the size to be 2 because SetUp() added two elements
    EXPECT_EQ(processor.get_size(), 2);
}

TEST_F(DummyDataProcessorTest, CanAddNewValuesSuccessfully) {
    // Act: Add a new value
    processor.add_value(30);

    // Assert: Verify the state
    EXPECT_EQ(processor.get_size(), 3);
    EXPECT_EQ(processor.data.back(), 30);
}

TEST_F(DummyDataProcessorTest, ClearDataRemovesAllElements) {
    // Act: Clear the data
    processor.clear_data();

    // Assert: The container should be empty
    EXPECT_EQ(processor.get_size(), 0);
    EXPECT_TRUE(processor.data.empty());
}
