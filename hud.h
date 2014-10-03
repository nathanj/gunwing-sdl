#pragma once

#include "graphics.h"

class Hud {
public:
        static Texture image_bomb_, image_medal_;
        static void loadContent(Graphics& graphics);

        void draw(Graphics& graphics);
        void drawLives(Graphics& graphics);
        void drawMedals(Graphics& graphics);
        void drawBombs(Graphics& graphics);
};
