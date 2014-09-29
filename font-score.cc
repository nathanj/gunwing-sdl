#include "font-score.h"

#include <string>

// static
Texture FontScore::image_;

void FontScore::loadContent(Graphics& graphics)
{
        image_ = graphics.loadImage("scorefont2.png");
}

void FontScore::draw(Graphics& graphics, int score, float x, float y)
{
        char buf[16];
        snprintf(buf, sizeof(buf), "%09d", score);
        x -= width_;
        int first = 0;
        for (char c : std::string(buf)) {
                x += width_;
                first++;
                if (c == ' ')
                        continue;
                int n = c - '0';
                Color color1{1, 1, 1, 1};
                Color color2{0.3f, 0.3f, 0.3f, 0.2f};
                if (first < 4)
                        color1 = {1, 0.9f, 0.9f, 1};

                graphics.blit(image_, n * width_, 0, x + 2, y + 2,
                              width_, height_, Graphics::BlitFlags::NONE,
                              &color2);
                graphics.blit(image_, n * width_, 0, x, y, width_, height_,
                              Graphics::BlitFlags::NONE, &color1);
        }
}
