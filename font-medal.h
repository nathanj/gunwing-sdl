#pragma once

#include "graphics.h"
#include "vector.h"

class FontMedal {
public:
        static Texture image_;
        static void loadContent(Graphics& graphics);
        static void draw(Graphics& graphics, int count, float x, float y);

private:
        static const int width_ = 20;
        static const int height_ = 20;
};
