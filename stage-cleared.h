#pragma once

#include "sprite.h"
#include "timer.h"

class StageCleared : public Sprite
{
  public:
        static Texture image_;
        static void loadContent(Graphics &graphics);

        StageCleared();
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);

  private:
        Timer lifetime_{std::chrono::milliseconds(5000)};
};
