#pragma once

#include "graphics.h"

class FontScore {
public:
        static Texture image_;
        static void loadContent(Graphics& graphics);
        static void draw(Graphics& graphics, int score, float x, float y);

private:
        static const int width_ = 20;
        static const int height_ = 20;
};
