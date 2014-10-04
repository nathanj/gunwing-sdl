#pragma once

#include <chrono>
#include "graphics.h"

class Hud {
public:
        static Texture image_bomb_, image_medal_;
        static void loadContent(Graphics& graphics);

        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);
        void drawLives(Graphics& graphics);
        void drawMedals(Graphics& graphics);
        void drawBombs(Graphics& graphics);
private:
        float bomb_current_alpha_{1.f};
};
