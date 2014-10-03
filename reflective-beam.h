#pragma once

#include "sprite.h"

class ReflectiveBeam : public Sprite {
public:
        static Texture image_;
        static void loadContent(Graphics& graphics);

        ReflectiveBeam(float x, float y, float dx, float dy,
                       float left_wall, float right_wall);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);

private:
        float left_wall_, right_wall_;
};
