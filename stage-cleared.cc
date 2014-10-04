#include "stage-cleared.h"

Texture StageCleared::image_;
void StageCleared::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("stageclear.png");
}

StageCleared::StageCleared()
{
        position_ = {100, 100};
        direction_ = {0, 0};
}

void StageCleared::update(std::chrono::milliseconds delta)
{
        lifetime_.update(delta);
        if (!lifetime_.active())
                dead_ = true;
}

void StageCleared::draw(Graphics &graphics)
{
        if (lifetime_.elapsed().count() < 1000)
                return;

        graphics.blit(image_, 0, 0, position_.x, position_.y);
}
