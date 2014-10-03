#include "hud.h"

#include "game-state.h"
#include "font-medal.h"
#include "font-score.h"

Texture Hud::image_bomb_;
Texture Hud::image_medal_;
void Hud::loadContent(Graphics& graphics)
{
        image_bomb_ = graphics.loadImage("bombicon.png");
        image_medal_ = graphics.loadImage("medal.png");
}

void Hud::draw(Graphics& graphics)
{
        drawLives(graphics);
        drawMedals(graphics);
        drawBombs(graphics);
        FontMedal::draw(graphics, GameState::ship->medal_count(), 60, 32);
        FontScore::draw(graphics, GameState::ship->score(), 0, 0);
}

void Hud::drawLives(Graphics& graphics)
{
        auto pos = Vector<float>{10.f, 75.f};
        for (int i = 0; i < GameState::ship->lives(); i++) {
                const Texture& img = Ship::image_;
                graphics.blit(img, 0, 0, pos.x, pos.y,
                              img.w * 0.75f, img.h * 0.75f);
                pos.x += 25.f;
        }
}

void Hud::drawMedals(Graphics& graphics)
{
        auto pos = Vector<float>{40.f, 38.f};
        graphics.blit(image_medal_, 0, 0, pos.x, pos.y);
}

void Hud::drawBombs(Graphics& graphics)
{
        // todo - alpha?
        auto pos = Vector<float>{0.f, 570.f};
        for (int i = 0; i < GameState::ship->bombs(); i++) {
                graphics.blit(image_bomb_, 0, 0, pos.x, pos.y);
                pos.x += 24.f;
        }
}
