#pragma once

#include "sprite.h"
#include "timer.h"

class Enemy : public Sprite
{
  public:
        static Texture image_;

        static void loadContent(Graphics &graphics);

        Enemy(float x, float y, float dx, float dy);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);

  private:
        Timer time_to_next_bullet_;
        Timer time_to_next_state_;
        const std::chrono::milliseconds time_between_bullets_{1500};
        float angle_;

        enum class States
        {
                DOWN, SHOOTING, UP
        } state_;

        void fireBullet();
};
