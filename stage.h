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
	void update(std::chrono::milliseconds delta);
	void draw(Graphics& graphics);
	bool next_stage() { return next_stage_; }

protected:
	std::deque<std::pair<std::chrono::milliseconds, std::shared_ptr<Sprite>>> enemies_to_appear_;
	std::shared_ptr<Background> background_;

private:
	std::chrono::milliseconds time_{std::chrono::milliseconds(0)};
	bool stage_over_{false};
	bool next_stage_{false};
};
