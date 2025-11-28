#include <gtest/gtest.h>

class LifecycleTest : public ::testing::Test
{
  protected:
    // 1. CONSTRUCTOR (Hàm tạo)
    LifecycleTest()
    {
        std::cout << "  -> [1] Constructor: Create new Object at " << this << std::endl;
    }

    // 5. DESTRUCTOR (Hàm hủy)
    ~LifecycleTest() override
    {
        std::cout << "  -> [5] Destructor: Destroy Object at " << this << "\n" << std::endl;
    }

    // 2. SETUP (Chuẩn bị trước mỗi test)
    void SetUp() override
    {
        std::cout << "  -> [2] SetUp: Prepare resources" << std::endl;
    }

    // 4. TEARDOWN (Dọn dẹp sau mỗi test)
    void TearDown() override
    {
        std::cout << "  -> [4] TearDown: Clean resources" << std::endl;
    }
};

// --- TEST CASE 1 ---
TEST_F(LifecycleTest, TestCase_A)
{
    std::cout << "  -> [3] RUNNING TEST A LOGIC..." << std::endl;
}

// --- TEST CASE 2 ---
TEST_F(LifecycleTest, TestCase_B)
{
    std::cout << "  -> [3] RUNNING TEST B LOGIC..." << std::endl;
}
