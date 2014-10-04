#include "reflective-beam.h"

Texture ReflectiveBeam::image_;
void ReflectiveBeam::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("elecbullet.png");
}

ReflectiveBeam::ReflectiveBeam(float x, float y, float dx, float dy,
                               float left_wall, float right_wall)
{
        position_ = {x, y};
        direction_ = {dx, dy};
        direction_.normalize();
        speed_ = 3.f;
        left_wall_ = left_wall;
        right_wall_ = right_wall;
        geometry_.push_back({0, 0, (float)image_.w, (float)image_.h});
}

void ReflectiveBeam::update(std::chrono::milliseconds delta)
{
        // todo - delta
        position_.x += direction_.x * speed_;
        position_.y += direction_.y * speed_;

        if (position_.x < -32 || position_.x > Graphics::SCREEN_WIDTH)
                dead_ = true;
        if (position_.y < -32 || position_.y > Graphics::SCREEN_HEIGHT)
                dead_ = true;

        // Reverse direction when we hit the walls.
        if (position_.x < left_wall_ || position_.x > right_wall_)
                direction_.x = -direction_.x;
}

void ReflectiveBeam::draw(Graphics &graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y);
}
