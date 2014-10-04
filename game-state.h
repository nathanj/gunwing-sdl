#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include "ship.h"
#include "bullet.h"
#include "sprite.h"
#include "medal.h"
#include "enemy-chunk.h"
#include "graphics.h"
#include "hud.h"
#include "stage.h"
#include "title-screen.h"
#include "input.h"

class GameState
{
  public:
        static Ship *ship;
        static Hud *hud;
        static std::shared_ptr<Stage> stage;
        static std::shared_ptr<TitleScreen> title_screen;
        static std::vector<std::shared_ptr<Sprite>> background_enemy_bullets;
        static std::vector<std::shared_ptr<Sprite>> enemy_bullets;
        static std::vector<std::shared_ptr<Sprite>> enemies;
        static std::vector<Medal> medals;
        static std::vector<EnemyChunk> chunks;

        static void initialize();
        static void handleInput(const Input &input);
        static void update(std::chrono::milliseconds delta);
        static void draw(Graphics &graphics);
        static void convertBulletsToMedals();
        static void nextStage();

        static enum State {
                TITLE_SCREEN,
                CHOOSE_PILOT,
                STAGE_ONE,
                STAGE_TWO,
                HIGH_SCORE,
                GAME_OVER
        } state_;
};
