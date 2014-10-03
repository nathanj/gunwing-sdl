#pragma once

#include "sprite.h"

class ElectricBall : public Sprite {
public:
        static Texture image_;
        static void loadContent(Graphics& graphics);

        ElectricBall(float x, float y, float dx, float dy, float speed);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);
};
