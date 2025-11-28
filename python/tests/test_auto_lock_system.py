import pytest
from unittest.mock import Mock
# Phải import theo cấu trúc package: src.auto_lock_system
from src.auto_lock_system import AutoLockSystem

# CẤU TRÚC TEST (Arrange-Act-Assert)

def test_system_should_not_lock_initially():
    """Kiểm tra khi mới khởi động, không có lý do gì để khóa."""
    # ARRANGE
    mock_clock = Mock()
    system = AutoLockSystem(mock_clock)
    
    # ACT & ASSERT
    assert system.update(15.0) is False

def test_system_starts_timer_on_speed_increase():
    """Kiểm tra việc đặt mốc thời gian khi tốc độ vừa vượt ngưỡng."""
    # ARRANGE
    # Mock.return_value = Giá trị trả về cho lần gọi hàm
    mock_clock = Mock()
    mock_clock.get_time.return_value = 1000 # Giả lập thời gian bắt đầu là 1000ms
    system = AutoLockSystem(mock_clock)
    
    # ACT
    system.update(25.0) # Tốc độ vượt ngưỡng
    
    # ASSERT (Kiểm tra State: Mốc thời gian đã được lưu đúng chưa)
    assert system.time_ == 1000

def test_system_should_lock_after_5_seconds():
    """
    Kiểm tra kịch bản cốt lõi: Xe chạy nhanh liên tục trong > 5000ms.
    (Giống kịch bản WillOnce/WillOnce trong C++)
    """
    # ARRANGE
    # Mock cho phép ta thiết lập chuỗi giá trị trả về theo thứ tự
    mock_clock = Mock()
    # set up side_effect để trả về các giá trị khác nhau mỗi lần gọi:
    # Lần 1 (Bắt đầu): 1000ms
    # Lần 2 (Sau 6s): 7000ms
    mock_clock.get_time.side_effect = [1000, 7000] 
    
    system = AutoLockSystem(mock_clock)
    
    # ACT 1: Bắt đầu đếm (lần gọi thứ 1 -> trả về 1000)
    system.update(30.0) 
    assert system.time_ == 1000 # Kiểm tra mốc thời gian

    # ACT 2: Kiểm tra sau 6s (lần gọi thứ 2 -> trả về 7000)
    is_locked = system.update(30.0)
    
    # ASSERT
    assert is_locked is True
