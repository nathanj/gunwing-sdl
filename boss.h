#pragma once

#include <vector>

#include "sprite.h"
#include "timer.h"
#include "healthbar.h"

class Boss : public Sprite
{
  public:
        static Texture image_;

        Boss(float x, float y);
        static void loadContent(Graphics &graphics);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);

  private:
        Timer time_to_next_bullet_{std::chrono::milliseconds(70)};
        Timer invulnerable_{std::chrono::milliseconds(500)};
        const int max_health_{80000};
        std::vector<int> healthbar_markers_{{60000, 30000, 0}};
        HealthBar healthbar_;

        enum States {
                DOWN,
                LEFT,
                RIGHT
        } state_{DOWN};
        enum Forms {
                ONE,
                TWO,
                THREE,
                FOUR
        } form_{ONE};

        int shrapnel_rounds_;
        bool fire_left_;
        float angle_{0};

        void fireBullet(std::chrono::milliseconds delta);
        void fireShrapnel(std::chrono::milliseconds delta);
        void fireCircularBullets(std::chrono::milliseconds delta);
        void nextForm();
        void die();
};
