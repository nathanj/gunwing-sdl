#include "medal-plus.h"

#include "game-state.h"
#include "font-small.h"
#include "utils.h"

void MedalPlus::update(std::chrono::milliseconds delta)
{
        lifetime_.update(delta);
}

void MedalPlus::draw(Graphics& graphics)
{
        if (!lifetime_.active())
                return;

        position_ = {
                GameState::ship->position().x + 32 + direction_.x * speed_ * lifetime_.percent_elapsed(),
                GameState::ship->position().y -  3 + direction_.y * speed_ * lifetime_.percent_elapsed(),
        };

        float alpha = 1.0f * lifetime_.percent_left();
        FontSmall::draw(graphics, number_, position_.x, position_.y, alpha);
        FontSmall::draw(graphics, number_, position_.x + 1, position_.y + 1, alpha/4);
        FontSmall::draw(graphics, number_, position_.x + 2, position_.y + 2, alpha/8);
}

void MedalPlus::activate(int number)
{
        number_ = number;
        lifetime_.reset();
}
