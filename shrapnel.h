#pragma once

#include "sprite.h"

class Shrapnel : public Sprite {
public:
	static Texture image_;
	static void loadContent(Graphics& graphics);

	Shrapnel(float x, float y, float dx, float dy);
	void update(std::chrono::milliseconds delta);
	void draw(Graphics& graphics);
private:
};
