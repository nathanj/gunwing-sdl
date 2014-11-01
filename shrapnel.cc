#include "shrapnel.h"

#include "utils.h"
#include "game-state.h"

// static
Texture Shrapnel::image_;
void Shrapnel::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("shrapnel.png");
}

Shrapnel::Shrapnel(float x, float y, float dx, float dy)
{
        position_ = {x, y};
        direction_ = {dx, dy};
        direction_.normalize();
        speed_ = 120;
        geometry_.push_back({2, 2, 4, 4});
}

void Shrapnel::update(std::chrono::milliseconds delta)
{
        position_.x += direction_.x * speed_ * delta.count() / 1000.0f;
        position_.y += direction_.y * speed_ * delta.count() / 1000.0f;

        if (position_.x < -32 || position_.x > Graphics::SCREEN_WIDTH)
                dead_ = true;
        if (position_.y < -32 || position_.y > Graphics::SCREEN_HEIGHT)
                dead_ = true;
        if (GameState::ship->bomb() && collides(*GameState::ship->bomb()))
                dead_ = true;
}

void Shrapnel::draw(Graphics &graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y);
}
