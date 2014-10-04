#pragma once

#include <vector>

#include "sprite.h"
#include "timer.h"
#include "healthbar.h"

class Boss2 : public Sprite
{
  public:
        static Texture image_;
        static void loadContent(Graphics &graphics);

        Boss2(float x, float y);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);

  private:
        Timer time_to_next_bullet_{std::chrono::milliseconds(700)};
        Timer time_to_next_large_bullet_{std::chrono::milliseconds(350)};
        Timer invulnerable_{std::chrono::milliseconds(500)};
        const int max_health_{120000};
        std::vector<int> healthbar_markers_{{90000, 40000, 0}};
        HealthBar healthbar_;
        float angle_{0};

        enum States {
                DOWN,
                NORMAL
        } state_{DOWN};
        enum Forms {
                ONE,
                TWO,
                THREE
        } form_{ONE};

        void fireBullet();
        void fireElectricBeam();
        void fireLargeBullet();
        void nextForm();
        void die();
};
