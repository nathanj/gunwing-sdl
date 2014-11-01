#include "warning.h"

Texture Warning::image_;

void Warning::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("warning.png");
}

void Warning::update(std::chrono::milliseconds delta)
{
        lifetime_.update(delta);

        alpha_ += d_alpha_ * delta.count() / 1000.0f;
        if (alpha_ <= 0) {
                if (!lifetime_.update(delta))
                        dead_ = true;
                alpha_ = 0;
                d_alpha_ = -d_alpha_;
        } else if (alpha_ >= 1) {
                alpha_ = 1;
                d_alpha_ = -d_alpha_;
        }
}

void Warning::draw(Graphics &graphics)
{
        Graphics::BlitOptions options;
        options.color = Color{1, 1, 1, alpha_};
        graphics.blit(image_, 0, 0, 60, 100, options);
}
