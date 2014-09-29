#pragma once

#include "sprite.h"
#include "timer.h"

class HealthBar : public Sprite {
public:
	static Texture image_;
	static Texture marker_;
	static void loadContent(Graphics& graphics);
	HealthBar(int& health, int max_health, std::vector<int> markers);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);

private:
	int& health_;
	int max_health_;
	std::vector<int> markers_;
	Timer growing_{std::chrono::milliseconds(2000)};
};
