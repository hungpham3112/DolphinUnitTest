class AutoLockSystem:
    """
    Hệ thống khóa cửa tự động.
    Logic: Khóa cửa nếu xe chạy nhanh (>20km/h) trong quá 5 giây (5000ms).
    """
    def __init__(self, clock):
        """
        Dependency Injection:
        Python sử dụng Duck Typing. Tham số 'clock' ở đây có thể là bất cứ thứ gì,
        miễn là nó có method .get_time() trả về số.
        
        Trong Production: Truyền RealClock.
        Trong Testing: Truyền Mock Object.
        """
        self.clock = clock
        self.time_ = 0  # 0 nghĩa là chưa bắt đầu đếm

    def update(self, speed: float) -> bool:
        LOCK_THRESHOLD_MS = 5000
        REQUIRED_SPEED = 20.0

        if speed > REQUIRED_SPEED:
            # Logic: Nếu lần đầu vượt tốc độ -> Ghi lại mốc thời gian bắt đầu
            if self.time_ == 0:
                self.time_ = self.clock.get_time()
            else:
                # Logic: Nếu đã vượt tốc độ từ trước -> Kiểm tra xem đã trôi qua bao lâu
                current_time = self.clock.get_time()
                elapsed = current_time - self.time_
                
                # Nếu thời gian trôi qua lớn hơn 5s -> Khóa cửa
                if elapsed > LOCK_THRESHOLD_MS:
                    return True 
        else:
            # Logic: Nếu xe đi chậm lại -> Reset bộ đếm
            self.time_ = 0
            
        return False
