#include "healthbar.h"

#include "utils.h"

Texture HealthBar::image_;
Texture HealthBar::marker_;
void HealthBar::loadContent(Graphics &graphics)
{
        image_ = graphics.loadImage("healthbar.png");
        marker_ = graphics.loadImage("healthmarker.png");
}

HealthBar::HealthBar(int &health, int max_health, std::vector<int> markers)
    : health_(health), max_health_(max_health), markers_(markers)
{
        health_ = health;
        position_ = {60, 33};
}

void HealthBar::update(std::chrono::milliseconds delta)
{
        growing_.update(delta);
}

void HealthBar::draw(Graphics &graphics)
{
        float percentage = 1.0f * health_ / max_health_;
        float fade = growing_.percent_elapsed();
        Vector<float> pos = position_;

        // pos.x += image_.w / 2 * (1 - fade);
        // float len = image_.w * percentage;

        // bar
        Graphics::BlitOptions options;
        options.color = Color{1, 1, 1, 0.9f};
        options.sprite_w = image_.w * percentage * fade;
        options.sprite_h = image_.h / 2;
        graphics.blit(image_, 0, image_.h / 2, pos.x, pos.y, options);

        // outline
        options.sprite_w = image_.w * fade;
        options.color.a = 1;
        graphics.blit(image_, 0, 0, pos.x, pos.y, options);

        if (fade == 1) {
                for (float m : markers_) {
                        if (m == 0)
                                continue;

                        percentage = m / max_health_;
                        graphics.blit(marker_, 0, 0,
                                      pos.x + image_.w * percentage, pos.y);
                }
        }
}
