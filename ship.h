#pragma once

#include "sprite.h"
#include "timer.h"
#include "input.h"
#include "bullet.h"
#include "medal-plus.h"
#include "bomb.h"
#include "music.h"

class Ship : public Sprite
{
  public:
        static Texture image_shield_;
        static Texture image_;
        static Texture image2_;
        static Music::Sound laser_, collect_medal_, explosion_;

        Ship(float x = 220, float y = 520, int type = 1);

        static void loadContent(Graphics &graphics);

        void initialize();
        void handleInput(const Input &input);
        void update(std::chrono::milliseconds);
        void draw(Graphics &graphics);
        void fireBullet();

        int score()
        {
                return score_;
        }
        void score(int s)
        {
                score_ = std::min(s, 999999999);
        }
        int medal_count()
        {
                return medal_count_;
        }
        int lives()
        {
                return lives_;
        }
        bool game_over()
        {
                return game_over_;
        }
        int bombs()
        {
                return bombs_;
        }
        Bomb *bomb()
        {
                return bomb_.get();
        }
        std::vector<Bullet> &bullets()
        {
                return bullets_;
        }
        void type(int type)
        {
                type_ = type;
        }

  private:
        bool game_over_;
        int bombs_;
        int lives_;
        int medal_count_{0};
        int score_{0};
        int type_{1};
        std::vector<Bullet> bullets_;
        MedalPlus medal_plus_;
        Timer invinicibility_time_;
        Timer respawn_time_;
        Timer bullet_cooldown_;
        Timer laser_sound_cooldown_{std::chrono::milliseconds(100)};
        std::shared_ptr<Bomb> bomb_;

        void fireBomb();
        void die();
        void respawn();
        void collectMedals();
        void handleCollisions(const Sprite &sprite);
        int bulletStrength();
};
