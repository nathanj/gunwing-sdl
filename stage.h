#pragma once

#include <chrono>
#include <deque>
#include <memory>

#include "sprite.h"
#include "graphics.h"
#include "background.h"
#include "timer.h"

class Stage {
public:
	Stage();
	void update(std::chrono::milliseconds delta);
	void draw(Graphics& graphics);
protected:
	std::deque<std::pair<std::chrono::milliseconds, std::shared_ptr<Sprite>>> enemies_to_appear_;
	std::chrono::milliseconds time_;
	bool stage_over_{false};
	bool next_stage_{false};
	std::shared_ptr<Background> background_;
};
