#pragma once

#include <chrono>

#include "graphics.h"
#include "vector.h"

class Background
{
  public:
        static Texture clouds_, background2_, background3_;

        Background(Texture &background);
        static void loadContent(Graphics &graphics);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics &graphics);
        void fadeOut();

  private:
        Texture &background_;
        Vector<float> position_[2];
        float alpha_;
        enum class State
        {
                FADE_IN, NORMAL, FADE_OUT
        } state_;
};
