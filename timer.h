#pragma once

#include <chrono>

class Timer
{
  public:
        Timer(std::chrono::milliseconds duration = std::chrono::milliseconds(0))
            : duration_(duration), remaining_(duration)
        {
        }
        bool active() const
        {
                return remaining_.count() > 0;
        }
        void reset()
        {
                remaining_ = duration_;
        }
        void reset(std::chrono::milliseconds duration)
        {
                remaining_ = duration_ = duration;
        }
        void stop()
        {
                remaining_ = std::chrono::milliseconds(0);
        }

        bool update(std::chrono::milliseconds delta)
        {
                bool a = active();
                if (!a)
                        return a;
                remaining_ -= delta;
                if (remaining_.count() < 0)
                        remaining_ = std::chrono::milliseconds(0);
                return a;
        }

        float percent_remaining() const
        {
                return ((float)remaining_.count() / duration_.count());
        }
        float percent_elapsed() const
        {
                return 1.0f - percent_remaining();
        }
        std::chrono::milliseconds elapsed() const
        {
                return duration_ - remaining_;
        }
        std::chrono::milliseconds remaining() const
        {
                return remaining_;
        }

  private:
        std::chrono::milliseconds duration_;
        std::chrono::milliseconds remaining_;
};
