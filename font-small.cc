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
                Graphics::BlitOptions options;
                options.color = Color{1, 1, 1, alpha};
                options.sprite_w = width_;
                options.sprite_h = height_;
                graphics.blit(image_, n * width_, 0, x, y, options);
                x += width_;
        }
}
