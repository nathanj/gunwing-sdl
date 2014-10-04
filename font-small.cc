#include "font-small.h"
#include <string>

Texture FontSmall::image_;

void FontSmall::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("smallfont.png");
}

void FontSmall::draw(Graphics &graphics, int number, float x, float y,
                     float alpha)
{
        std::string output = "+" + std::to_string(number);
        for (char c : output) {
                int n = c == '+' ? 10 : c - '0';
                Color color{1, 1, 1, alpha};
                graphics.blit(image_, n * width_, 0, x, y, width_, height_,
                              Graphics::BlitFlags::NONE, &color);
                x += width_;
        }
}
