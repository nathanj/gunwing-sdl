#pragma once

#include "sprite.h"
#include "timer.h"

class ShrapnelEnemy : public Sprite {
public:
	static Texture image_;
	static void loadContent(Graphics& graphics);

	ShrapnelEnemy(float x, float y);
	void update(std::chrono::milliseconds delta);
	void draw(Graphics& graphics);
private:
	Vector<float> start_position_;
	Timer time_to_next_bullet_;
	Timer time_to_next_state_{std::chrono::milliseconds(1000)};
	const std::chrono::milliseconds time_between_bullets_{1500};

	enum class States { DOWN, SHOOTING, UP } state_;

	void fireBullet();
};
