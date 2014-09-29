#pragma once

#include "sprite.h"
#include "timer.h"

class Medal : public Sprite {
public:
	static Texture image_;

	Medal(float x, float y);
	static void loadContent(Graphics& graphics);
	void update(std::chrono::milliseconds delta);
	void draw(Graphics& graphics);

	bool obtainable() { return !delay_time_.active(); }

private:
	Timer delay_time_{std::chrono::milliseconds(300)};
};
