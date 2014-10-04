#pragma once

#include <chrono>
#include "graphics.h"

class TitleScreen
{
  public:
        static Texture image_, image_press_;
        static void loadContent(Graphics& graphics);

        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);

  private:
        float alpha_{0.f};
        float dir_{.5f};
};
