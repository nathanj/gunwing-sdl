#include "enemy-chunk.h"

#include "utils.h"
#include "game-state.h"

// static
Texture EnemyChunk::images_[3];
void EnemyChunk::loadContent(Graphics &graphics)
{
        images_[0] = graphics.loadImage("enemy_chunk1.png");
        images_[1] = graphics.loadImage("enemy_chunk2.png");
        images_[2] = graphics.loadImage("enemy_chunk3.png");
}

EnemyChunk::EnemyChunk(float x, float y)
{
        position_ = {x, y};
        direction_ = {rand_between(-64, 64) / 64.0f,
                      rand_between(-64, 64) / 64.0f};
        direction_.normalize();

        speed_ = 2 + gaussrand() * 1.0f;
        type_ = rand_between(0, 3);
        max_alpha_ = 30;
        lifetime_.reset(std::chrono::milliseconds(1000));

        geometry_.push_back({0, 0, (float)images_[0].w, (float)images_[0].h});
}

void EnemyChunk::update(std::chrono::milliseconds delta)
{
        lifetime_.update(delta);

        if (!lifetime_.active())
                dead_ = true;

        // todo - delta
        position_.x += direction_.x * speed_;
        position_.y += direction_.y * speed_;
}

void EnemyChunk::draw(Graphics &graphics)
{
        float alpha = 0.8f * lifetime_.percent_remaining();
        Color color{1, 1, 1, alpha};
        graphics.blit(images_[type_], 0, 0, position_.x, position_.y,
                      images_[type_].w, images_[type_].h,
                      Graphics::BlitFlags::NONE, &color);
}

void createChunks(const Vector<float> &position, const Vector<int> &dimensions,
                  int chunks)
{
        for (int i = 0; i < chunks; i++) {
                EnemyChunk ch(position.x + rand_between(0, dimensions.x),
                              position.y + rand_between(0, dimensions.y));
                GameState::chunks.push_back(ch);
        }
}
