#pragma once

#include <SDL_ttf.h>
#include "graphics.h"

class Text {
public:
        static void loadContent(Graphics& graphics);
        static void drawString(Graphics& graphics, const std::string& str, int x, int y);

private:
        static int size_;
        static Texture alphabet_[100];
        static TTF_Font *font_;
};
