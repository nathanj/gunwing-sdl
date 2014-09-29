#pragma once

#include "graphics.h"

class FontSmall {
public:
        static Texture image_;
        static void loadContent(Graphics& graphics);
        static void draw(Graphics& graphics, int number, float x, float y,
                         float alpha);

private:
        static const int width_ = 4;
        static const int height_ = 5;
};
