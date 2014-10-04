#pragma once

#include <iostream>
#include "math.h"

struct Rectangle
{
        float x, y, w, h;
        bool collides(const Rectangle &b) const
        {
                const Rectangle &a = *this;
                return (a.x < b.x + b.w && b.x < a.x + a.w && a.y < b.y + b.h &&
                        b.y < a.y + a.h);
        }
};

template <typename T>
struct Vector
{
        T x, y;
        T length() const
        {
                return static_cast<T>(sqrtf(x * x + y * y));
        }
        void normalize()
        {
                if (x == 0 || y == 0)
                        return;
                float len = length();
                x /= len;
                y /= len;
        }

        static T distance(const Vector<T> &a, const Vector<T> &b)
        {
                T x = a.x - b.x;
                T y = a.y - b.y;

                return static_cast<T>(sqrtf(x * x + y * y));
        }
};

template <typename T>
Vector<T> operator-(const Vector<T> &a, const Vector<T> &b)
{
        return {a.x - b.x, a.y - b.y};
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vector<T> &b)
{
        os << "(" << b.x << " " << b.y << ")";
        return os;
}
