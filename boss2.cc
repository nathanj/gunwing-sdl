#include "boss2.h"

#include <cassert>
#include "game-state.h"
#include "shrapnel-bomb.h"
#include "enemy-chunk.h"
#include "utils.h"
#include "electric-beam.h"
#include "electric-ball.h"
#include "reflective-beam.h"

using ms = std::chrono::milliseconds;

Texture Boss2::image_;
void Boss2::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("boss3.png");
}

Boss2::Boss2(float x, float y)
    : healthbar_(health_, max_health_, healthbar_markers_)
{
        position_ = {x, y};
        direction_ = {0, 1};
        speed_ = 3;
        health_ = max_health_;

        geometry_.push_back({34, 15, 310, 184});
        geometry_.push_back({73, 183, 28, 49});
        geometry_.push_back({273, 183, 28, 49});
        geometry_.push_back({128, 193, 20, 20});
        geometry_.push_back({237, 193, 20, 20});
}

void Boss2::update(std::chrono::milliseconds delta)
{
        time_to_next_bullet_.update(delta);
        time_to_next_large_bullet_.update(delta);
        invulnerable_.update(delta);
        healthbar_.update(delta);

        if (state_ != States::DOWN && !invulnerable_.active()) {
                for (auto &b : GameState::ship->bullets()) {
                        if (!b.dead() && collides(b)) {
                                b.dead(true);
                                health_ -= b.strength();
                        }
                }
                if (GameState::ship->bomb() &&
                    collides(*GameState::ship->bomb())) {
                        auto dps = GameState::ship->bomb()->damage_per_second();
                        health_ -= dps * delta.count() / 1000.f;
                }
        }

        if (health_ < 0) {
                dead_ = true;
                die();
                return;
        }

        if (!time_to_next_bullet_.active() && state_ != States::DOWN) {
                if (form_ == Forms::ONE)
                        time_to_next_bullet_.reset(ms(700));
                else
                        time_to_next_bullet_.reset(ms(700 / 5));
                fireBullet();
        }

        if (state_ != States::DOWN &&
            (form_ == Forms::ONE || form_ == Forms::THREE))
                fireElectricBeam();

        if (!time_to_next_large_bullet_.active() && state_ != States::DOWN &&
            (form_ == Forms::TWO || form_ == Forms::THREE)) {
                if (form_ == Forms::THREE)
                        time_to_next_large_bullet_.reset(ms(350 / 2));
                else
                        time_to_next_large_bullet_.reset(ms(350));
                fireLargeBullet();
        }

        if (state_ == States::DOWN && position_.y > 20) {
                state_ = States::NORMAL;
                direction_ = {0, 0};
                speed_ = 1;
                invulnerable_.stop();
        }

        if (health_ < healthbar_markers_[(int)form_])
                nextForm();

        // todo - delta
        position_.x += direction_.x * speed_;
        position_.y += direction_.y * speed_;
}

void Boss2::draw(Graphics &graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y);
        healthbar_.draw(graphics);
}

void Boss2::fireElectricBeam()
{
        GameState::background_enemy_bullets.emplace_back(
            std::make_shared<ElectricBeam>(position_.x + 68,
                                           position_.y + 220));
        GameState::background_enemy_bullets.emplace_back(
            std::make_shared<ElectricBeam>(position_.x + 270,
                                           position_.y + 220));
}

void Boss2::fireBullet()
{
        if (GameState::ship->dead())
                return;

        if (form_ == Forms::ONE) {
                angle_ += 0.03f;
                auto angle2_ = angle_ + 0.5f;
                auto d = Vector<float>{std::abs(cosf(-angle_ * 2 * M_PI)),
                                       std::abs(sinf(-angle_ * 2 * M_PI))};
                auto d2 = Vector<float>{std::abs(cosf(-angle2_ * 2 * M_PI)),
                                        std::abs(sinf(-angle2_ * 2 * M_PI))};
                d.normalize();
                d2.normalize();

                for (int i = 0; i < 3; i++) {
                        GameState::enemy_bullets.emplace_back(
                            std::make_shared<ReflectiveBeam>(
                                position_.x + 120 + d.x * i * 5,
                                position_.y + 200 + d.y * i * 5, d.x, d.y,
                                position_.x + 98, position_.y + 290));
                        GameState::enemy_bullets.emplace_back(
                            std::make_shared<ReflectiveBeam>(
                                position_.x + 240 + d2.x * i * 5,
                                position_.y + 200 + d2.y * i * 5, d2.x, d2.y,
                                position_.x + 98, position_.y + 290));
                }
        } else if (form_ == Forms::TWO) {
                angle_ += 0.03f;
                float speed = 2.f;

                for (int i = 0; i < 2; i++) {
                        GameState::enemy_bullets.emplace_back(
                            std::make_shared<Bullet>(
                                position_.x + 55, position_.y + 40,
                                cosf(-angle_ * 2 * M_PI + i * M_PI) / 2,
                                std::abs(sinf(-angle_ * 2 * M_PI + i * M_PI)),
                                speed));
                        GameState::enemy_bullets.emplace_back(
                            std::make_shared<Bullet>(
                                position_.x + 315, position_.y + 40,
                                cosf(angle_ * 2 * M_PI + i * M_PI) / 2,
                                std::abs(sinf(angle_ * 2 * M_PI + i * M_PI)),
                                speed));
                }
        }
}

void Boss2::fireLargeBullet()
{
        if (GameState::ship->dead())
                return;

        angle_ += 0.03f;

        GameState::enemy_bullets.emplace_back(std::make_shared<ElectricBall>(
            position_.x + 55, position_.y + 40, cosf(-angle_ * 2 * M_PI) / 2,
            std::abs(sinf(-angle_ * 2 * M_PI)), 1));
        GameState::enemy_bullets.emplace_back(std::make_shared<ElectricBall>(
            position_.x + 315, position_.y + 40, cosf(angle_ * 2 * M_PI) / 2,
            std::abs(sinf(angle_ * 2 * M_PI)), 1));
}

void Boss2::nextForm()
{
        form_++;
        invulnerable_.reset();
        GameState::convertBulletsToMedals();
        Vector<int> dimensions = {image_.w, image_.h};
        createChunks(position_, dimensions, 100);
}

void Boss2::die()
{
        createMedals(position_, 2);
        GameState::convertBulletsToMedals();
        Vector<int> dimensions = {image_.w, image_.h};
        createChunks(position_, dimensions, 300);
}
