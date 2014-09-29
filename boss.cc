#include "boss.h"

#include <cassert>
#include "game-state.h"
#include "shrapnel-bomb.h"

using ms = std::chrono::milliseconds;

Texture Boss::image_;

Boss::Boss(float x, float y)
{
        position_ = {x, y};
        direction_ = {0, 1};
        speed_ = 3;
        health_ = max_health_;
        dead_ = false;
        angle_ = 0;

        shrapnel_rounds_ = 5;
        fire_left_ = true;

        geometry_.push_back( {50, 30, 50, 170} );
        geometry_.push_back( {300, 30, 50, 170} );
        geometry_.push_back( {95, 80, 50, 60} );
        geometry_.push_back( {250, 85, 50, 60} );
        geometry_.push_back( {156, 16, 85, 170} );
        geometry_.push_back( {170, 8, 50, 200} );
        geometry_.push_back( {183, 8, 30, 230} );
}

void Boss::loadContent(Graphics& graphics)
{
        image_ = graphics.loadImage("boss2.png");
}

void Boss::update(std::chrono::milliseconds delta)
{
        time_to_next_bullet_.update(delta);
        invulnerable_.update(delta);

        for (auto& b : GameState::ship->bullets()) {
                if (!b.dead() && collides(b)) {
                        b.dead(true);
                        health_ -= b.strength();
                }
        }

        if (health_ <= 0) {
                dead_ = true;
                return;
        }

        if (!time_to_next_bullet_.active() && state_ != States::DOWN) {
                switch (form_) {
                case ONE:
                        time_to_next_bullet_.reset(ms(30 * 70));
                        break;
                case TWO:
                        time_to_next_bullet_.reset(ms(70));
                        break;
                case THREE:
                        time_to_next_bullet_.reset(ms(50));
                        break;
		default:
			assert(0);
                }
                fireBullet();
        }

        if (state_ == States::DOWN && position_.y > 20) {
                state_ = States::LEFT;
                direction_ = {-1, 0};
                speed_ = 1;
                invulnerable_.stop();
        } else if (state_ == States::LEFT && position_.x < -10) {
                state_ = States::RIGHT;
                direction_ = {1, 0};
        } else if (state_ == States::RIGHT && position_.x > 80) {
                state_ = States::LEFT;
                direction_ = {-1, 0};
        }

        // todo -delta
        position_.x += direction_.x * speed_;
        position_.y += direction_.y * speed_;
}

void Boss::draw(Graphics& graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y);
}

void Boss::fireBullet()
{
        if (GameState::ship->dead())
                return;

        if (form_ == Forms::ONE) {
		Vector<float> pos = { position_.x + 60, position_.y + 200 };
		if (!fire_left_)
			pos = { position_.x + 310, position_.y + 200 };

		GameState::enemy_bullets.push_back(
			std::make_shared<ShrapnelBomb>(
				pos.x, pos.y, 0, 1, shrapnel_rounds_));

		fire_left_ = !fire_left_;
		shrapnel_rounds_ += 4;
	} else {
		angle_ += 0.03f; // todo - delta

		for (int i = 0; i < 4; i++) {
			GameState::enemy_bullets.push_back(
				std::make_shared<Bullet>(
					position_.x + image_.w / 4 - 20,
					position_.y + 120,
					cosf(-angle_ * 2 * M_PI + i * 2 * M_PI / 4),
					sinf(-angle_ * 2 * M_PI + i * 2 * M_PI / 4),
					1.2));
			GameState::enemy_bullets.push_back(
				std::make_shared<Bullet>(
					position_.x + 3*image_.w / 4 + 15,
					position_.y + 120,
					cosf(angle_ * 2 * M_PI + i * 2 * M_PI / 4),
					sinf(angle_ * 2 * M_PI + i * 2 * M_PI / 4),
					1.2));
		}
	}
}
