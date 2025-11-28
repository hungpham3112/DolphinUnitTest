#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Return; // Để dùng lệnh Return()

// --- 1. ABSTRACT LAYER (Interface) ---
// Định nghĩa cái "khuôn" của cảm biến. Code thật hay Mock đều phải theo khuôn này.
class ITemperatureSensor
{
  public:
    virtual ~ITemperatureSensor()
    {
    } // Destructor ảo là bắt buộc
    virtual float get_temperature() = 0; // Hàm thuần ảo
};

// --- 2. CODE CẦN TEST (Production Code) ---
// Class này không quan tâm sensor là thật hay giả, miễn là có hàm get_temperature()
class EngineController
{
    ITemperatureSensor &sensor; // Dependency Injection (Bơm phụ thuộc)
  public:
    EngineController(ITemperatureSensor &s) : sensor(s)
    {
    }

    bool is_safe_to_start()
    {
        float temp = sensor.get_temperature();
        if (temp > 100.0)
        {
            return false; // Quá nóng, không an toàn
        }
        return true;
    }
};

// --- 3. MOCK CLASS (Diễn viên đóng thế) ---
class MockSensor : public ITemperatureSensor
{
  public:
    // MOCK_METHOD(Kiểu_trả_về, Tên_hàm, (Tham_số...), (Override));
    MOCK_METHOD(float, get_temperature, (), (override));
};

// --- 4. TEST CASE ---
TEST(EngineTest, should_not_start_when_too_hot)
{
    // A. Arrange (Chuẩn bị)
    MockSensor mock_sensor;

    // Lập trình hành vi cho Mock (Stubbing):
    // "Này Mock, tí nữa ai gọi hàm get_temperature thì trả về 105.0 ngay nhé"
    EXPECT_CALL(mock_sensor, get_temperature()).WillOnce(Return(105.0));

    EngineController engine(mock_sensor);

    // B. Act (Hành động) & C. Assert (Khẳng định)
    // Vì nhiệt độ 105 > 100 -> Hàm phải trả về false
    EXPECT_FALSE(engine.is_safe_to_start());
}

TEST(EngineTest, ShouldStartWhenCool)
{
    MockSensor mock_sensor;

    // Lần này giả lập nhiệt độ mát (80 độ)
    EXPECT_CALL(mock_sensor, get_temperature()).WillOnce(Return(80.0));

    EngineController engine(mock_sensor);
    EXPECT_TRUE(engine.is_safe_to_start());
}
