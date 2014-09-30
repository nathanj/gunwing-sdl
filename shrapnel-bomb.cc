#include "shrapnel-bomb.h"

#include "game-state.h"
#include "shrapnel.h"
#include "utils.h"

// static
Texture ShrapnelBomb::image_;
void ShrapnelBomb::loadContent(Graphics& graphics)
{
        image_ = graphics.loadImage("shrapnel_bomb.png");
}

ShrapnelBomb::ShrapnelBomb(float x, float y, float dx, float dy, int shrapnel)
{
        position_ = {x, y};
        direction_ = {dx, dy};
        direction_.normalize();

        speed_ = 5;
        shrapnel_count_ = shrapnel;
        health_ = 50;
        geometry_.push_back( {5, 5, 25, 25} );
}

void ShrapnelBomb::update(std::chrono::milliseconds delta)
{
        if (health_ < 0) {
                dead_ = true;
                createMedals(position_);
        }

        for (auto& b : GameState::ship->bullets()) {
                if (!b.dead() && collides(b)) {
                        b.dead(true);
                        health_ -= b.strength();
                }
        }

        if (!dead()) {
                // todo - delta
                position_.x += direction_.x * speed_;
                position_.y += direction_.y * speed_;
        }

        if (position_.y < 0 || position_.y + image_.h > Graphics::SCREEN_HEIGHT ||
            position_.x < 0 || position_.x + image_.w > Graphics::SCREEN_WIDTH ||
            dead()) {
                dead_ = true;
                for (int i = 0; i < shrapnel_count_; i++) {
                        float dx = cosf(i * 2 * M_PI / shrapnel_count_);
                        float dy = sinf(i * 2 * M_PI / shrapnel_count_);
                        GameState::enemy_bullets.push_back(
                                std::make_shared<Shrapnel>(
                                        position_.x + image_.w / 2,
                                        position_.y + image_.h / 2,
                                        dx, dy));
                }
        }
}

void ShrapnelBomb::draw(Graphics& graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y);
}
