#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "graphics.h"

class Text
{
  public:
        static void loadContent(Graphics& graphics);
        static void drawString(Graphics& graphics, const std::string& str,
                               int x, int y, Color* color = NULL);
        static void drawChar(Graphics& graphics, char c, int x, int y,
                             Color* color = NULL);

  private:
        static int size_;
        static Texture alphabet_[200];
        static TTF_Font* font_;
};
