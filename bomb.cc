#include "bomb.h"

#include "game-state.h"

Texture Bomb::image_;
void Bomb::loadContent(Graphics& graphics)
{
        image_ = graphics.loadImage("bomb.png");
}

Bomb::Bomb(float x, float y)
{
        position_ = {x, y};
        direction_ = {0.f, 0.f};

        geometry_.push_back( {50, 0, 200, 682} );
        geometry_.push_back( {64, 591, 182, 207} );
        geometry_.push_back( {85, 760, 135, 169} );
        geometry_.push_back( {112, 890, 83, 90} );
}

void Bomb::update(std::chrono::milliseconds delta)
{
        lifetime_.update(delta);
        if (!lifetime_.active())
                dead_ = true;

        position_ = GameState::ship->position();
        position_.x += -image_.w / 2 + 8;
        position_.y += -image_.h + 15;
}

void Bomb::draw(Graphics& graphics)
{
        auto alpha = lifetime_.percent_left();
        auto color = Color{1, 1, 1, alpha};
        graphics.blit(image_, 0, 0, position_.x, position_.y, -1, -1,
                      Graphics::BlitFlags::NONE, &color);
}
