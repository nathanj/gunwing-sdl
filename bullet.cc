#include "bullet.h"

#include <string>
#include "game-state.h"

// static
Texture Bullet::image_;
Texture Bullet::image2_;

Bullet::Bullet(float x, float y, float dx, float dy, float speed, int strength,
               int type)
    : strength_(strength), type_(type)
{
        position_ = {x, y};
        direction_ = {dx, dy};
        direction_.normalize();
        speed_ = speed * 60;
        geometry_.push_back({2, 2, 8, 8});
}

// static
void Bullet::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("ebullet.png");
        image2_ = graphics.loadImage("bullet.png");
}

void Bullet::update(std::chrono::milliseconds delta)
{
        position_.x += direction_.x * speed_ * delta.count() / 1000.0f;
        position_.y += direction_.y * speed_ * delta.count() / 1000.0f;

        if (position_.x < -32 || position_.x > Graphics::SCREEN_WIDTH)
                dead_ = true;
        if (position_.y < -32 || position_.y > Graphics::SCREEN_HEIGHT)
                dead_ = true;
}

void Bullet::draw(Graphics &graphics)
{
        if (type_ == 1)
                graphics.blit(image_, 0, 0, position_.x, position_.y);
        else
                graphics.blit(image2_, 0, 0, position_.x, position_.y);
}
