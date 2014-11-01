#include "medal.h"

#include "utils.h"
#include "game-state.h"

// static
Texture Medal::image_;

Medal::Medal(float x, float y)
{
        position_ = {x, y};
        direction_ = {rand_between(-100, 100) / 100.0f,
                      rand_between(-100, 100) / 100.0f};
        direction_.normalize();
        speed_ = 60 * (rand() % 3 + 1);

        geometry_.push_back(
            {0, 0, static_cast<float>(image_.w), static_cast<float>(image_.h)});
}

// static
void Medal::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("medal.png");
}

void Medal::update(std::chrono::milliseconds delta)
{
        delay_time_.update(delta);

        if (!delay_time_.active()) {
                Vector<float> newdir = {(GameState::ship->position().x +
                                         Ship::image_.w / 2 - image_.w / 2) -
                                            position_.x,
                                        (GameState::ship->position().y +
                                         Ship::image_.h / 2 - image_.h / 2) -
                                            position_.y};
                newdir.normalize();

                // Average the new direction with the previous direction
                // with the weight depending on the distance from the
                // medal to the ship.
                Vector<float> distance =
                    GameState::ship->position() - position_;
                int len = distance.length();

                if (len < 50)
                        len = 1;
                else if (len < 200)
                        len = 2;
                else
                        len = 3;

                direction_.x = (len * direction_.x + (4 - len) * newdir.x) / 4;
                direction_.y = (len * direction_.y + (4 - len) * newdir.y) / 4;

                speed_ += 60 * 0.2f;
        }

        position_.x += direction_.x * speed_ * delta.count() / 1000.0f;
        position_.y += direction_.y * speed_ * delta.count() / 1000.0f;
}

void Medal::draw(Graphics &graphics)
{
        graphics.blit(image_, 0, 0, position_.x, position_.y, image_.w,
                      image_.h);
}
