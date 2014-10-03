#pragma once

#include "sprite.h"
#include "timer.h"
#include "input.h"
#include "bullet.h"
#include "medal-plus.h"
#include "bomb.h"

class Ship : public Sprite {
public:
        static Texture image_shield_;
        static Texture image_;

        Ship();

        static void loadContent(Graphics& graphics);

        void initialize();
        void handleInput(const Input& input);
        void update(std::chrono::milliseconds);
        void draw(Graphics& graphics);

	int score() { return score_; }
	void score(int s) { score_ = std::min(s, 999999999); }
	int medal_count() { return medal_count_; }
	int lives() { return lives_; }
	int bombs() { return bombs_; }
	Bomb* bomb() { return bomb_.get(); }

	std::vector<Bullet> bullets() { return bullets_; }

private:
        bool game_over_;
        int bombs_;
        int lives_;
        int medal_count_{0};
        int score_{0};
        int type_;
        std::vector<Bullet> bullets_;
        MedalPlus medal_plus_;
        Timer invinicibility_time_;
        Timer respawn_time_;
        Timer bullet_cooldown_;
	std::shared_ptr<Bomb> bomb_;

        void fireBullet();
	void fireBomb();
	void die();
	void respawn();
	void collectMedals();
	void handleCollisions(const Sprite& sprite);
};
