#pragma once

#include "sprite.h"
#include "timer.h"

class EnemyChunk : public Sprite {
public:
        static Texture images_[3];
        static void loadContent(Graphics& graphics);

        EnemyChunk(float x, float y);
        void update(std::chrono::milliseconds delta);
        void draw(Graphics& graphics);

protected:
        float time_;
        int type_;
        float max_alpha_;
        Timer lifetime_;
        int r_, g_, b_;
};

void createChunks(const Vector<float>& position);
