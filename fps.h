#include <chrono>

class FramesPerSecond {
public:
	bool update(std::chrono::milliseconds delta)
	{
		ticks_ += delta;
		frames_++;
		if (ticks_.count() > 1000) {
			fps_ = frames_ * 1000 / ticks_.count();
			ticks_ = std::chrono::milliseconds(0);
			frames_ = 0;
			return true;
		}
		return false;
	}
	int fps() { return fps_; }
private:
	std::chrono::milliseconds ticks_{0};
	int frames_{0};
	int fps_{0};
};
