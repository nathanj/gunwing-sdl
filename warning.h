#pragma once

#include <chrono>

#include "graphics.h"
#include "sprite.h"
#include "timer.h"

class Warning : public Sprite
{
  public:
        static Texture image_;
        static void loadContent(Graphics &graphics);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);

  private:
        float alpha_{1};
        float d_alpha_{-0.60f};
        Timer lifetime_{std::chrono::milliseconds(5000)};
};
