#include "stage.h"
#include <iostream>

#include "game-state.h"
#include "utils.h"

Stage::Stage()
{
}

void Stage::update(std::chrono::milliseconds delta)
{
	background_->update(delta);

	time_ += delta;

	//if (enemies_to_appear_.size() > 1) {
	while (enemies_to_appear_.size() > 0 &&
	       enemies_to_appear_[0].first < time_) {
		GameState::enemies.push_back(enemies_to_appear_.front().second);
		enemies_to_appear_.pop_front();
	}

	//} else if (enemies_to_appear_.size() == 1) {
	//	GameState::enemies.push_back(enemies_to_appear_.front().second);
	//	enemies_to_appear_.pop_front();
	//}
}

void Stage::draw(Graphics& graphics)
{
	background_->draw(graphics);
}

