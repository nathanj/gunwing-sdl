#pragma once

#include <chrono>
#include <memory>
#include "graphics.h"
#include "vector.h"
#include "input.h"
#include "ship.h"

class ChoosePilot
{
  public:
        static Texture image_;
        static Texture image_selection_;
        static void loadContent(Graphics& graphics);

        ChoosePilot();
        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);
        void handleInput(const Input& input);

        int selection() const
        {
                return selection_;
        }
        bool finished() const
        {
                return finished_;
        }

  private:
        int selection_;
        bool finished_{false};
        Vector<float> position_[4];
        Vector<float> final_position_;
        std::shared_ptr<Ship> ship_;

        void moveSelection();
};
