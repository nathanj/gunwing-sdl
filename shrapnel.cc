#include "shrapnel.h"

#include "utils.h"

// static
Texture Shrapnel::image_;
void Shrapnel::loadContent(Graphics& graphics)
{
	image_ = graphics.loadImage("shrapnel.png");
}

Shrapnel::Shrapnel(float x, float y, float dx, float dy)
{
        LOG("Here");
	position_ = {x, y};
	direction_ = {dx, dy};
	direction_.normalize();
	speed_ = 4;
	geometry_.push_back( {2, 2, 4, 4} );
}

void Shrapnel::update(std::chrono::milliseconds )
{
        LOG("here");
	// todo - delta
	position_.x += direction_.x * speed_;
	position_.y += direction_.y * speed_;

	if (position_.x < -32 || position_.x > 480)
		dead_ = true;
	if (position_.y < -32 || position_.y > 600)
		dead_ = true;
}

void Shrapnel::draw(Graphics& graphics)
{
        LOG("here");
	graphics.blit(image_, 0, 0, position_.x, position_.y);
}
