#include "sprite.h"

bool Sprite::collides(const Sprite &other) const
{
        for (const Rectangle &a : geometry_) {
                Rectangle c = a;
                c.x += position().x;
                c.y += position().y;
                for (const Rectangle &b : other.geometry_) {
                        Rectangle d = b;
                        d.x += other.position().x;
                        d.y += other.position().y;
                        if (c.collides(d))
                                return true;
                }
        }
        return false;
}
