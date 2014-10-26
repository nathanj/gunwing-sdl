#include "shrapnel-enemy.h"

#include "game-state.h"
#include "utils.h"
#include "shrapnel-bomb.h"
#include "music.h"
#include "enemy.h"

// static
Texture ShrapnelEnemy::image_;

void ShrapnelEnemy::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("shrapnelenemy.png");
}

ShrapnelEnemy::ShrapnelEnemy(float x, float y)
{
        position_ = {x, y};
        start_position_ = {x, y};

        direction_ = {0, 1};
        speed_ = 2;
        health_ = 2000;
        dead_ = false;

        time_to_next_bullet_.reset(time_between_bullets_);
        state_ = States::DOWN;

        geometry_.push_back({0, 0, (float)image_.w, (float)image_.h});
}

void ShrapnelEnemy::update(std::chrono::milliseconds delta)
{
        time_to_next_state_.update(delta);
        time_to_next_bullet_.update(delta);

        if (!time_to_next_state_.active()) {
                if (state_ == States::DOWN) {
                        state_ = States::SHOOTING;
                        direction_ = {0, 0};
                        time_to_next_bullet_.reset(time_between_bullets_);
                        time_to_next_state_.reset(
                            std::chrono::milliseconds(10000));
                        fireBullet();
                } else if (state_ == States::SHOOTING) {
                        state_ = States::UP;
                        direction_ = {0, -1};
                }
        }

        for (auto &b : GameState::ship->bullets()) {
                if (!b.dead() && collides(b)) {
                        Music::playSound(Ship::laser_);
                        b.dead(true);
                        health_ -= b.strength();
                }
        }
        if (GameState::ship->bomb() && collides(*GameState::ship->bomb())) {
                auto dps = GameState::ship->bomb()->damage_per_second();
                health_ -= dps * delta.count() / 1000.f;
        }

        if (position_.y < -200)
                dead_ = true;

        // todo - delta
        position_.x += direction_.x * speed_;
        position_.y += direction_.y * speed_;

        if (health_ < 0) {
                Music::queueSound(Enemy::explosion_);
                dead_ = true;
                createMedals(position_);
        }

        if (!time_to_next_bullet_.active() && state_ == States::SHOOTING) {
                time_to_next_bullet_.reset(time_between_bullets_);
                fireBullet();
        }
}

void ShrapnelEnemy::draw(Graphics &graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y);
}

void ShrapnelEnemy::fireBullet()
{
        // Don't shoot while the player is dead.
        if (GameState::ship->dead())
                return;

        GameState::enemy_bullets.push_back(std::make_shared<ShrapnelBomb>(
            position_.x + 16, position_.y + 32, 0, 1, 20));
}
