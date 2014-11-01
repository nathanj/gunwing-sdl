#include "hud.h"

#include "game-state.h"
#include "font-medal.h"
#include "font-score.h"

Texture Hud::image_bomb_;
Texture Hud::image_medal_;
void Hud::loadContent(Graphics &graphics)
{
        image_bomb_ = graphics.loadImage("bombicon.png");
        image_medal_ = graphics.loadImage("medal.png");
}

void Hud::update(std::chrono::milliseconds)
{
        auto target_alpha = 1.f;
        if (GameState::ship->position().x < 70 &&
            GameState::ship->position().y > 550)
                target_alpha = 0.1f;

        bomb_current_alpha_ += (target_alpha - bomb_current_alpha_) / 10.f;
}

void Hud::draw(Graphics &graphics)
{
        drawLives(graphics);
        drawMedals(graphics);
        drawBombs(graphics);
        FontMedal::draw(graphics, GameState::ship->medal_count(), 310, 0);
        FontScore::draw(graphics, GameState::ship->score(), 0, 0);
}

void Hud::drawLives(Graphics &graphics)
{
        auto pos = Vector<float>{10.f, 30.f};
        for (int i = 0; i < GameState::ship->lives(); i++) {
                const Texture &img = Ship::image_;
                Graphics::BlitOptions options;
                options.scale_h = 0.75;
                options.scale_w = 0.75;
                graphics.blit(img, 0, 0, pos.x, pos.y, options);
                pos.x += 25.f;
        }
}

void Hud::drawMedals(Graphics &graphics)
{
        auto pos = Vector<float>{300.f, 2.f};
        graphics.blit(image_medal_, 0, 0, pos.x, pos.y);
}

void Hud::drawBombs(Graphics &graphics)
{
        auto pos = Vector<float>{0.f, Graphics::SCREEN_HEIGHT - 48.f};
        Graphics::BlitOptions options;
        options.color = Color{1, 1, 1, bomb_current_alpha_};
        for (int i = 0; i < GameState::ship->bombs(); i++) {
                graphics.blit(image_bomb_, 0, 0, pos.x, pos.y, options);
                pos.x += 24.f;
        }
}
