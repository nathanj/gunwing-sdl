#include "stage.h"
#include <iostream>

#include "game-state.h"
#include "utils.h"
#include "stage-cleared.h"
#include "music.h"

void Stage::update(std::chrono::milliseconds delta)
{
        background_->update(delta);

        time_ += delta;

        while (enemies_to_appear_.size() > 0 &&
               enemies_to_appear_[0].first < time_) {
                if (enemies_to_appear_.size() == 2)
                        Music::stopMusic(std::chrono::milliseconds(3000));
                if (enemies_to_appear_.size() == 1)
                        Music::playMusic("boss.mp3", std::chrono::milliseconds(1000));
                GameState::enemies.push_back(enemies_to_appear_.front().second);
                enemies_to_appear_.pop_front();
        }

        if (enemies_to_appear_.empty() && GameState::enemies.empty()) {
                if (!stage_over_) {
                        LOG("stage over!");
                        stage_over_ = true;
                        GameState::enemies.emplace_back(
                            std::make_shared<StageCleared>());
                        Music::stopMusic(std::chrono::milliseconds(2000));
                } else {
                        if (background_->done())
                                next_stage_ = true;
                        background_->fadeOut();
                }
        }
}

void Stage::draw(Graphics &graphics)
{
        background_->draw(graphics);
}
