#include "electric-beam.h"

Texture ElectricBeam::image_;
void ElectricBeam::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("elecbeam.png");
}

ElectricBeam::ElectricBeam(float x, float y, float dx, float dy, float speed)
{
        position_ = {x, y};
        direction_ = {dx, dy};
        direction_.normalize();
        speed_ = speed * 60;
        geometry_.push_back({3, 0, 26, 32});
}

void ElectricBeam::update(std::chrono::milliseconds delta)
{
        position_.x += direction_.x * speed_ * delta.count() / 1000.0f;
        position_.y += direction_.y * speed_ * delta.count() / 1000.0f;

        if (position_.x < -32 || position_.x > Graphics::SCREEN_WIDTH)
                dead_ = true;
        if (position_.y < -32 || position_.y > Graphics::SCREEN_HEIGHT)
                dead_ = true;
}

void ElectricBeam::draw(Graphics &graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y);
}
