#include "choose-pilot.h"

#include "game-state.h"

Texture ChoosePilot::image_;
Texture ChoosePilot::image_selection_;
void ChoosePilot::loadContent(Graphics& graphics)
{
        image_ = graphics.loadImage("choosepilot.png");
        image_selection_ = graphics.loadImage("selection.png");
}

ChoosePilot::ChoosePilot()
{
        ship_ = std::make_shared<Ship>(240, 300);
        selection_ = 1;

        for (auto& e : position_) {
                e.x = 53;
                e.y = 410;
        }
        final_position_ = {53, 410};
}

void ChoosePilot::update(std::chrono::milliseconds delta)
{
        ship_->fireBullet();
        ship_->update(delta);
        for (int i = 0; i < 4; i++) {
                position_[i].x +=
                    (final_position_.x - position_[i].x) / (i + 8);
                position_[i].y +=
                    (final_position_.y - position_[i].y) / (i + 8);
        }
}

void ChoosePilot::draw(Graphics& graphics)
{
        graphics.blit(image_, 0, 0, 0, 0);
        for (int i = 0; i < 4; i++)
                graphics.blit(image_selection_, 0, 0, position_[i].x,
                              position_[i].y, -1, -1, Graphics::BlitFlags::NONE,
                              NULL, 1, 1, .25f * 4 - i);
        ship_->draw(graphics);
}

void ChoosePilot::handleInput(const Input& input)
{
        if ((input.wasKeyPressed(SDLK_SPACE) || input.getButton(0)))
                finished_ = true;

        Vector<float> axis = input.getAxis();
        if (input.wasKeyPressed(SDLK_LEFT) || input.wasKeyPressed(SDLK_RIGHT) ||
            std::abs(axis.x) > 32600)
                moveSelection();
}

void ChoosePilot::moveSelection()
{
        selection_ = selection_ == 1 ? 2 : 1;
        if (selection_ == 1)
                final_position_ = {53, 410};
        else
                final_position_ = {289, 410};
        ship_->type(selection_);
}
