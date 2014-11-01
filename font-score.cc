#include "font-score.h"

#include <string>

// static
Texture FontScore::image_;

void FontScore::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("scorefont2.png");
}

void FontScore::draw(Graphics &graphics, int score, float x, float y)
{
        char buf[16];
        snprintf(buf, sizeof(buf), "%09d", score);
        x -= width_;
        int first = 0;
        Graphics::BlitOptions options, options2;
        options.color = Color{1, 1, 1, 1};
        options.sprite_h = height_;
        options.sprite_w = width_;
        options2.color = Color{0.3f, 0.3f, 0.3f, 0.2f};
        options2.sprite_h = height_;
        options2.sprite_w = width_;
        for (char c : std::string(buf)) {
                x += width_;
                first++;
                if (c == ' ')
                        continue;
                int n = c - '0';
                if (first < 4)
                        options.color = {1, 0.9f, 0.9f, 1};
                else
                        options.color = {1, 1, 1, 1};

                graphics.blit(image_, n * width_, 0, x + 2, y + 2, options2);
                graphics.blit(image_, n * width_, 0, x, y, options);
        }
}
