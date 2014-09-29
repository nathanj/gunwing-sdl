#pragma once

#include "sprite.h"
#include "timer.h"

class Boss : public Sprite {
public:
        static Texture image_;

        Boss(float x, float y);
        static void loadContent(Graphics& graphics);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);

private:
        Timer time_to_next_bullet_{std::chrono::milliseconds(70)};
        Timer invulnerable_{std::chrono::milliseconds(70)};

        const int max_health_{130000};

        Vector<float> start_position_;

        enum States { DOWN, LEFT, RIGHT } state_{DOWN};
        enum Forms { ONE, TWO, THREE, FOUR } form_{ONE};

        int shrapnel_rounds_;
        bool fire_left_;
        float angle_{0};

        void fireBullet();
};
