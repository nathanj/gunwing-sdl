#include "enemy.h"

#include <algorithm>
#include "game-state.h"
#include "utils.h"
#include "enemy-chunk.h"
#include "ship.h"

using namespace std;

// static
Texture Enemy::image_;
Music::Sound Enemy::explosion_;

void Enemy::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("enemy.png");
        explosion_ = Music::loadSound("Explosion.wav");
}

Enemy::Enemy(float x, float y, float dx, float dy)
{
        position_ = {x, y};
        direction_ = {dx, dy};
        direction_.normalize();

        speed_ = 120;
        health_ = 300;
        dead_ = false;
        time_to_next_state_.reset(std::chrono::milliseconds(1500));

        time_to_next_bullet_ = time_between_bullets_;
        state_ = States::DOWN;

        geometry_.push_back({0, 0, (float)image_.w, (float)image_.h});
}

void Enemy::update(std::chrono::milliseconds delta)
{
        time_to_next_state_.update(delta);
        time_to_next_bullet_.update(delta);

        if (!time_to_next_state_.active()) {
                if (state_ == States::DOWN) {
                        state_ = States::SHOOTING;
                        direction_ = {0, 0};
                        time_to_next_bullet_.reset(time_between_bullets_);
                        time_to_next_state_.reset(
                            std::chrono::milliseconds(8500));
                } else if (state_ == States::SHOOTING) {
                        state_ = States::UP;
                        direction_ = {0, -1};
                        speed_ = 240;
                }
        }

        handleCollisionWithShipWeapons(this, GameState::ship.get(),
                                       delta.count() / 1000.0f);

        if (position_.y < -200 || position_.y > Graphics::SCREEN_HEIGHT)
                dead_ = true;

        if (health_ <= 0) {
                Music::queueSound(explosion_);
                dead_ = true;
                createMedals(position_);
                Vector<int> dimensions = {image_.w, image_.h};
                createChunks(position_, dimensions);
        }

        if (!time_to_next_bullet_.active()) {
                time_to_next_bullet_.reset();
                fireBullet();
        }

        position_.x += direction_.x * speed_ * delta.count() / 1000.0f;
        position_.y += direction_.y * speed_ * delta.count() / 1000.0f;

        auto vx = GameState::ship->position().x - position_.x;
        auto vy = GameState::ship->position().y - position_.y;
        angle_ = radians_to_degrees(-std::atan2(-vy, vx) - M_PI / 2);
}

void Enemy::draw(Graphics &graphics)
{
        Graphics::BlitOptions options;
        options.rotation = angle_;
        graphics.blit(image_, 0, 0, position_.x, position_.y, options);
}

void Enemy::fireBullet()
{
        // Don't shoot while the player is dead.
        if (GameState::ship->dead())
                return;

        float vx = GameState::ship->position().x + Ship::image_.w / 2 -
                   position_.x - 30 + rand() % 40;
        float vy = GameState::ship->position().y + Ship::image_.h / 2 -
                   position_.y - 30 + rand() % 40;

        GameState::enemy_bullets.emplace_back(std::make_shared<Bullet>(
            position_.x + image_.w / 2, position_.y + image_.h / 2, vx, vy, 3));
}
