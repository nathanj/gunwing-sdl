#pragma once

#include "sprite.h"

class ElectricBeam : public Sprite
{
  public:
        static Texture image_;
        static void loadContent(Graphics &graphics);

        ElectricBeam(float x, float y, float dx = 0, float dy = 1,
                     float speed = 5);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);
};
