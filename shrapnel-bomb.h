#pragma once

#include "sprite.h"

class ShrapnelBomb : public Sprite
{
  public:
        static Texture image_;
        static void loadContent(Graphics &graphics);

        ShrapnelBomb(float x, float y, float dx, float dy, int shrapnel);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);

  protected:
        int shrapnel_count_;
};
