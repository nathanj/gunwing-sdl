#include "electric-ball.h"

Texture ElectricBall::image_;
void ElectricBall::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("elecball.png");
}

ElectricBall::ElectricBall(float x, float y, float dx, float dy, float speed)
{
        position_ = {x, y};
        direction_ = {dx, dy};
        direction_.normalize();
        speed_ = speed * 60;
        geometry_.push_back({4, 4, image_.w - 8.f, image_.h - 8.f});
}

void ElectricBall::update(std::chrono::milliseconds delta)
{
        position_.x += direction_.x * speed_ * delta.count() / 1000.0f;
        position_.y += direction_.y * speed_ * delta.count() / 1000.0f;

        if (position_.x < -32 || position_.x > Graphics::SCREEN_WIDTH)
                dead_ = true;
        if (position_.y < -32 || position_.y > Graphics::SCREEN_HEIGHT)
                dead_ = true;
}

void ElectricBall::draw(Graphics &graphics)
{
        Graphics::BlitOptions options;
        options.color = {1, 1, 1, 0.7f};
        graphics.blit(image_, 0, 0, position_.x, position_.y, options);
}
