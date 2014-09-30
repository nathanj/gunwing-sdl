#pragma once

#include "sprite.h"

class Bullet : public Sprite {
public:
        static Texture image_;
        static Texture image2_;

        static void loadContent(Graphics& graphics);

        Bullet(float x, float y, float dx = 0.0, float dy = -1.0,
               float speed = 15.0, int strength = 20, int type = 1);
        void update(std::chrono::milliseconds );
        void draw(Graphics& graphics);

        int strength() { return strength_; }

protected:
        int strength_;
        int type_;
};
