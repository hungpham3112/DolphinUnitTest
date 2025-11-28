// 1. TEST PROGRAM

#include <gtest/gtest.h>

// 2. TEST SUITE: "CalculatorTests"

// 3. TEST: "Addition"
TEST(CalculatorTests, Addition)
{
    // Assertions
    EXPECT_EQ(1 + 1, 2);
}

// 3. TEST: "Subtraction"
TEST(CalculatorTests, Subtraction)
{
    EXPECT_EQ(5 - 2, 3);
}

// 3. TEST: "NotEqualString"
TEST(StringTests, NotEqualString)
{
    EXPECT_STRNE("hung", "pham");
}

// Entry point of Test Program
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
