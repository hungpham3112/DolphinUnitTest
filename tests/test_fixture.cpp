// ❌ BAD: Duplicate logic in every test
#include <gtest/gtest.h>

TEST(StackTest, PopReturnsLastElement)
{
    std::vector<int> stack;
    stack.push_back(10);
    stack.push_back(20);
    stack.push_back(30);

    stack.pop_back();
    EXPECT_EQ(stack.back(), 20);
}

TEST(StackTest, SizeIsCorrectAfterPush)
{
    std::vector<int> stack;
    stack.push_back(10);
    stack.push_back(20);
    stack.push_back(30);

    stack.push_back(40);
    EXPECT_EQ(stack.size(), 4);
}

// ✅ GOOD: Setup logic is isolated in a Class
class StackFixture : public ::testing::Test
{
  protected:
    std::vector<int> stack; // The shared state

    // Runs BEFORE each test
    void SetUp() override
    {
        stack.push_back(10);
        stack.push_back(20);
        stack.push_back(30);
    }

    // (Optional) Runs AFTER each test
    void TearDown() override
    {
        stack.clear();
    }
};

// Note: We use TEST_F (F = Fixture), not TEST
TEST_F(StackFixture, PopReturnsLastElement)
{
    // 'stack' is already filled with 10, 20, 30
    stack.pop_back();
    EXPECT_EQ(stack.back(), 20);
}

TEST_F(StackFixture, SizeIsCorrectAfterPush)
{
    // 'stack' is reset to 10, 20, 30 automatically
    stack.push_back(40);
    EXPECT_EQ(stack.size(), 4);
}
