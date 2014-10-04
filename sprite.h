#pragma once

#include <vector>
#include <chrono>
#include <algorithm>

#include "graphics.h"
#include "vector.h"

class Sprite
{
  public:
        Texture image;

        virtual ~Sprite()
        {
        }
        virtual void update(std::chrono::milliseconds delta) = 0;
        virtual void draw(Graphics &graphics) = 0;

        bool collides(const Sprite &other) const;

        const Vector<float> &position() const
        {
                return position_;
        }
        bool dead() const
        {
                return dead_;
        }
        void dead(bool value)
        {
                dead_ = value;
        }

  protected:
        bool dead_{false};
        float speed_{1.0};
        int health_{1};
        std::vector<Rectangle> geometry_;
        Vector<float> direction_{0, 0};
        Vector<float> position_{0, 0};
};

template <typename T>
inline void remove_dead(std::vector<T> &sprites)
{
        sprites.erase(std::remove_if(std::begin(sprites), std::end(sprites),
                                     [](const T & s) {
                return s.dead();
        }),
                      std::end(sprites));
}

template <typename T>
inline void remove_dead(std::vector<std::shared_ptr<T>> &sprites)
{
        sprites.erase(std::remove_if(std::begin(sprites), std::end(sprites),
                                     [](const std::shared_ptr<T> & s) {
                return s->dead();
        }),
                      std::end(sprites));
}
