#include "title-screen.h"

Texture TitleScreen::image_, TitleScreen::image_press_;
void TitleScreen::loadContent(Graphics& graphics)
{
        image_ = graphics.loadImage("title.png");
        image_press_ = graphics.loadImage("pressstart.png");
}

void TitleScreen::update(std::chrono::milliseconds delta)
{
        auto dt = delta.count() / 1000.f;

        alpha_ += dir_ * dt;
        if (alpha_ > 1.f) {
                alpha_ = 1.f;
                dir_ = -dir_;
        } else if (alpha_ < 0.f) {
                alpha_ = 0.f;
                dir_ = -dir_;
        }
}

void TitleScreen::draw(Graphics& graphics)
{
        auto color = Color{1, 1, 1, alpha_};
        graphics.blit(image_, 0, 0, 0, 0);
        graphics.blit(image_press_, 0, 0, 0, 250, -1, -1,
                      Graphics::BlitFlags::NONE, &color);
}
