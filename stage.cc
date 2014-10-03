#include "stage.h"
#include <iostream>

#include "game-state.h"
#include "utils.h"
#include "stage-cleared.h"

void Stage::update(std::chrono::milliseconds delta)
{
	background_->update(delta);

	time_ += delta;

	while (enemies_to_appear_.size() > 0 &&
	       enemies_to_appear_[0].first < time_) {
		GameState::enemies.push_back(enemies_to_appear_.front().second);
		enemies_to_appear_.pop_front();
	}

	if (enemies_to_appear_.empty() && GameState::enemies.empty()) {
		if (!stage_over_) {
			LOG("stage over!");
			stage_over_ = true;
			GameState::enemies.emplace_back(
				std::make_shared<StageCleared>());
		} else {
			LOG("next stage!");
			next_stage_ = true;
		}
	}
}

void Stage::draw(Graphics& graphics)
{
	background_->draw(graphics);
}

