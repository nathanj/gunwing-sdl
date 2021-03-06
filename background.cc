#include "background.h"

#include <algorithm>
#include "game-state.h"
#include "utils.h"

// static
Texture Background::clouds_, Background::background2_, Background::background3_;

Background::Background(Texture &background)
    : background_(background),
      position_{{0, 0}, {0, 0}},
      alpha_{0.01f},
      state_{State::FADE_IN}
{
}

// static
void Background::loadContent(Graphics &graphics)
{
        clouds_ = graphics.loadImage("bg.png");
        background2_ = graphics.loadImage("bg2.png");
        background3_ = graphics.loadImage("bg3.png");
}

void Background::update(std::chrono::milliseconds delta)
{
        position_[0].x = GameState::ship->position().x / 5;
        position_[0].x = std::max(-120.0f, position_[0].x);

        position_[0].y -= 180 * delta.count() / 1000.0f;
        if (position_[0].y < 0)
                position_[0].y += background_.h;

        position_[1].x = GameState::ship->position().x / 4;
        position_[1].x = std::max(-120.0f, position_[1].x);

        position_[1].y -= 1.0f;
        if (position_[1].y < 0)
                position_[1].y += clouds_.h;

        if (state_ == State::FADE_IN) {
                alpha_ *= 1.03f;
                if (alpha_ > 1.0f) {
                        alpha_ = 1.0f;
                        state_ = State::NORMAL;
                }
        } else if (state_ == State::FADE_OUT) {
                alpha_ *= 0.96f;
                if (alpha_ < 0.02f) {
                        alpha_ = 0.00f;
                        state_ = State::DONE;
                }
        }
}

void Background::draw(Graphics &graphics)
{
        Graphics::BlitOptions options;
        options.color = Color{1, 1, 1, alpha_};
        graphics.blit(background_, position_[0].x, position_[0].y, 0, 0,
                      options);
        graphics.blit(background_, position_[0].x,
                      position_[0].y - background_.h, 0, 0, options);

        options.color.a *= 0.1f;
        graphics.blit(clouds_, position_[1].x, position_[1].y, 0, 0, options);
        graphics.blit(clouds_, position_[1].x, position_[1].y - clouds_.h, 0, 0,
                      options);
}

void Background::fadeOut()
{
        state_ = State::FADE_OUT;
}
