#include "font-medal.h"

Texture FontMedal::image_;
void FontMedal::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("scorefont2.png");
}

void FontMedal::draw(Graphics &graphics, int count, float x, float y)
{
        char buf[16];
        snprintf(buf, sizeof(buf), "%05d", count);
        auto bufs = std::string(buf);
	Graphics::BlitOptions options;
	options.w = width_;
	options.h = height_;
	options.color = {1, 1, 1, .5};
        for (auto &c : bufs) {
                x += width_;
                int num = c == 'x' ? 10 : c - '0';
		options.color.alpha = 0.5;
                graphics.blit(image_, num * width_, 0, x + 1, y + 1, options);
		options.color.alpha = 1.0;
                graphics.blit(image_, num * width_, 0, x, y, options);
        }
}
