#include "bullet.h"

#include <string>

// static
Texture Bullet::image_;

Bullet::Bullet(float x, float y, float dx, float dy, float speed, int strength) :
	strength_(strength)
{
	position_ = {x, y};
	direction_ = {dx, dy};
	direction_.normalize();
	speed_ = speed;
	geometry_.push_back( {2,2,8,8} );
}

// static
void Bullet::loadContent(Graphics& graphics)
{
	image_ = graphics.loadImage("ebullet.png");
}

void Bullet::update(std::chrono::milliseconds )
{
	// todo - use delta
	position_.x += direction_.x * speed_;
	position_.y += direction_.y * speed_;

	dead_ = position_.x < -32 || position_.x > Graphics::SCREEN_WIDTH ||
		position_.y < -32 || position_.y > Graphics::SCREEN_HEIGHT;
}

void Bullet::draw(Graphics& graphics)
{
	graphics.blit(image_, 0, 0, position_.x, position_.y);
}
