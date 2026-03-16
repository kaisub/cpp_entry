
#include "stdafx.h"
#include "algorithms/algorithmsEntry.h"
#include "functionality.h"
#include "common/entryTestHelpers.h"

using testing::HasSubstr;
using testing::Not;

const std::vector<Functionality> handled_cases = {
    Functionality::PrintDir
};

// Test for handled Functionality enums
class AlgorithmsEntryHandledTest : public CoutRedirectTest,
                                   public testing::WithParamInterface<Functionality> {};

TEST_P(AlgorithmsEntryHandledTest, ExecutesWithoutUnhandledMessage) {
    EXPECT_NO_THROW({ algorithmsEntry(GetParam()); });
    // Verify that we do NOT hit the default case
    EXPECT_THAT(buffer.str(), Not(HasSubstr("unhandled functionality")));
}

INSTANTIATE_TEST_SUITE_P(
    HandledCases,
    AlgorithmsEntryHandledTest,
    testing::ValuesIn(handled_cases),
    funcPrinter);

// Test for NOT handled Functionality enums
class AlgorithmsEntryUnhandledTest : public CoutRedirectTest,
                                public testing::WithParamInterface<Functionality>
{
};

TEST_P(AlgorithmsEntryUnhandledTest, PrintsUnhandledMessage)
{
    EXPECT_NO_THROW({ algorithmsEntry(GetParam()); });
    // Verify that we DO hit the default case with correct ID
    std::string expected = "unhandled functionality: " + std::to_string(static_cast<int>(GetParam())) + "\n";
    EXPECT_EQ(buffer.str(), expected);
}

INSTANTIATE_TEST_SUITE_P(
    UnhandledCases,
    AlgorithmsEntryUnhandledTest,
    testing::ValuesIn(GetUnhandledFunctionalities(handled_cases)),
    funcPrinter);
