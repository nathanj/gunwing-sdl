#include "ship.h"

#include <iostream>
#include <algorithm>

#include "medal.h"
#include "game-state.h"
#include "medal-plus.h"
#include "utils.h"
#include "font-score.h"
#include "utils.h"

// static
Texture Ship::image_shield_;
Texture Ship::image_;
Texture Ship::image2_;
Music::Sound Ship::laser_;
Music::Sound Ship::collect_medal_;
Music::Sound Ship::explosion_;

Ship::Ship(float x, float y, int type)
    : invinicibility_time_(std::chrono::milliseconds(0)),
      respawn_time_(std::chrono::milliseconds(0)),
      bullet_cooldown_(std::chrono::milliseconds(50))
{
        position_ = {x, y};
        direction_ = {0, 0};
        speed_ = 5.0;
        lives_ = 2;
        invinicibility_time_.stop();
        respawn_time_.stop();
        game_over_ = false;
        bombs_ = 3;
        type_ = type;
        geometry_.push_back({14, 14, 2, 2});
}

// static
void Ship::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("ship.png");
        image2_ = graphics.loadImage("ship2.png");
        image_shield_ = graphics.loadImage("shield.png");
        laser_ = Music::loadSound("Laser_Shoot2.wav");
        collect_medal_ = Music::loadSound("Powerup.wav");
        explosion_ = Music::loadSound("Explosion.wav");
}

void Ship::handleInput(const Input &input)
{
        Vector<float> axis = input.getAxis();
        if (axis.x != 0 || axis.y != 0) {
                direction_ = axis;
                direction_.normalize();
        } else {
                direction_ = {0, 0};

                if (input.isKeyHeld(SDLK_LEFT))
                        direction_.x = -1;
                else if (input.isKeyHeld(SDLK_RIGHT))
                        direction_.x = 1;

                if (input.isKeyHeld(SDLK_DOWN))
                        direction_.y = 1;
                else if (input.isKeyHeld(SDLK_UP))
                        direction_.y = -1;

                direction_.normalize();
        }

        if (input.isKeyHeld(SDLK_SPACE) || input.isButtonHeld(0))
                fireBullet();

        if (input.isKeyHeld(SDLK_b) || input.isButtonHeld(1))
                fireBomb();
}

int Ship::bulletStrength()
{
        return type_ == 1 ? 30 : 25;
}

void Ship::fireBullet()
{
        if (bomb_ || bullet_cooldown_.active())
                return;

        if (!laser_sound_cooldown_.active()) {
                // Music::queueSound(laser_);
                laser_sound_cooldown_.reset();
        }
        bullet_cooldown_.reset();

        bullets_.emplace_back(position_.x + image_.w / 2 - 4, position_.y, 0,
                              -1, 15, bulletStrength(), 2);
        if (type_ == 1) {
                bullets_.emplace_back(position_.x + image_.w / 2 - 16,
                                      position_.y + 20, 0, -1, 15,
                                      bulletStrength(), 2);
                bullets_.emplace_back(position_.x + image_.w / 2 + 8,
                                      position_.y + 20, 0, -1, 15,
                                      bulletStrength(), 2);
        } else {
                bullets_.emplace_back(position_.x + image_.w / 2 - 12,
                                      position_.y + 15, -0.2f, -1, 15,
                                      bulletStrength(), 2);
                bullets_.emplace_back(position_.x + image_.w / 2 + 4,
                                      position_.y + 15, 0.2f, -1, 15,
                                      bulletStrength(), 2);
                bullets_.emplace_back(position_.x + image_.w / 2 - 16,
                                      position_.y + 20, -0.5f, -1, 15,
                                      bulletStrength(), 2);
                bullets_.emplace_back(position_.x + image_.w / 2 + 8,
                                      position_.y + 20, 0.5f, -1, 15,
                                      bulletStrength(), 2);
        }
}

void Ship::fireBomb()
{
        if (!bomb_ && bombs_ > 0) {
                bomb_ = std::make_shared<Bomb>(position_.x, position_.y);
                invinicibility_time_.reset();
                bombs_--;
                bullets_.clear();
        }
}

void Ship::update(std::chrono::milliseconds delta)
{
        bullet_cooldown_.update(delta);
        invinicibility_time_.update(delta);
        laser_sound_cooldown_.update(delta);
        if (bomb_)
                bomb_->update(delta);

        if (dead_) {
                respawn_time_.update(delta);
                if (!respawn_time_.active()) {
                        if (lives_ >= 0)
                                respawn();
                        else
                                game_over_ = true;
                }
                return;
        }

        for (const auto &b : GameState::background_enemy_bullets)
                handleCollisions(*b);
        for (const auto &b : GameState::enemy_bullets)
                handleCollisions(*b);
        for (const auto &b : GameState::enemies)
                handleCollisions(*b);

        // todo - use delta
        position_.x += direction_.x * speed_;
        position_.y += direction_.y * speed_;

        position_.x =
            clamp(position_.x, 0.0f, 1.0f * Graphics::SCREEN_WIDTH - image_.w);
        position_.y =
            clamp(position_.y, 0.0f, 1.0f * Graphics::SCREEN_HEIGHT - image_.h);

        collectMedals();

        for (auto &b : bullets_)
                b.update(delta);
        remove_dead(bullets_);

        if (bomb_ && bomb_->dead())
                bomb_.reset();

        medal_plus_.update(delta);
}

void Ship::handleCollisions(const Sprite &sprite)
{
        if (!sprite.dead() && collides(sprite)) {
                if (!invinicibility_time_.active())
                        die();
        }
}

void Ship::collectMedals()
{
        for (Medal &m : GameState::medals) {
                if (m.obtainable() && collides(m)) {
                        Music::queueSound(collect_medal_);
                        medal_count_++;
                        score(score() + medal_count_);
                        medal_plus_.activate(medal_count_);
                        m.dead(true);
                }
        }
}

void Ship::draw(Graphics &graphics)
{
        if (dead_)
                return;

        for (auto &b : bullets_)
                b.draw(graphics);
        medal_plus_.draw(graphics);

        const Texture &image = type_ == 1 ? image_ : image2_;
        graphics.blit(image, 0, 0, position_.x, position_.y);
        if (invinicibility_time_.active()) {
                float fade = invinicibility_time_.percent_remaining();
                Color color{1, 1, 1, fade};
                graphics.blit(image_shield_, 0, 0, position_.x - 8,
                              position_.y - 8, -1, -1,
                              Graphics::BlitFlags::NONE, &color);
        }

        if (bomb_)
                bomb_->draw(graphics);
}

void Ship::die()
{
        Music::queueSound(explosion_);
        dead_ = true;
        lives_--;
        bullets_.clear();
        respawn_time_.reset(std::chrono::milliseconds(2500));
        auto dimensions = Vector<int>{image_.w, image_.h};
        createChunks(position_, dimensions, 50);
}

void Ship::respawn()
{
        dead_ = false;
        invinicibility_time_.reset(std::chrono::milliseconds(4000));
        position_.y = 500;
        bombs_ = 3;
        // medal_count_ = 1;
}
