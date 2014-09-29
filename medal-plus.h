#pragma once

#include <chrono>

#include "sprite.h"
#include "timer.h"

class MedalPlus : public Sprite {
public:
        MedalPlus() { lifetime_.stop(); }
        virtual void update(std::chrono::milliseconds delta);
        virtual void draw(Graphics& graphics);
        void activate(int number);

private:
        int number_;
        Timer lifetime_{std::chrono::milliseconds(1000)};
};
