#pragma once

#include "sprite.h"
#include "timer.h"

class Bomb : public Sprite
{
  public:
        static Texture image_;
        static void loadContent(Graphics &graphics);

        Bomb(float x, float y);
        virtual void update(std::chrono::milliseconds delta);
        virtual void draw(Graphics &graphics);

        int damage_per_second()
        {
                return damage_per_second_;
        }

  private:
        static constexpr int damage_per_second_{8000};
        Timer lifetime_{std::chrono::milliseconds(2000)};
};
