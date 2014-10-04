#include "game-state.h"

#include "utils.h"
#include "stage1.h"
#include "stage2.h"

// static
Ship *GameState::ship;
Hud *GameState::hud;
std::shared_ptr<Stage> GameState::stage;
std::shared_ptr<TitleScreen> GameState::title_screen;
std::vector<std::shared_ptr<Sprite>> GameState::background_enemy_bullets;
std::vector<std::shared_ptr<Sprite>> GameState::enemy_bullets;
std::vector<std::shared_ptr<Sprite>> GameState::enemies;
std::vector<Medal> GameState::medals;
std::vector<EnemyChunk> GameState::chunks;
GameState::State GameState::state_{GameState::State::TITLE_SCREEN};

void GameState::initialize()
{
        title_screen = std::make_shared<TitleScreen>();
}

void GameState::handleInput(const Input &input)
{
        if (state_ == State::TITLE_SCREEN) {
                if ((input.isKeyHeld(SDLK_SPACE) || input.getButton(0)))
                        nextStage();
                return;
        }

        ship->handleInput(input);
}

void GameState::update(std::chrono::milliseconds delta)
{
        if (state_ == State::TITLE_SCREEN) {
                title_screen->update(delta);
                return;
        }

        if (stage)
                stage->update(delta);
        ship->update(delta);
        hud->update(delta);
        for (auto &e : enemies)
                e->update(delta);
        for (auto &e : medals)
                e.update(delta);
        for (auto &e : chunks)
                e.update(delta);
        for (unsigned int i = 0; i < enemy_bullets.size(); ++i)
                enemy_bullets[i]->update(delta);
        for (unsigned int i = 0; i < background_enemy_bullets.size(); ++i)
                background_enemy_bullets[i]->update(delta);

        remove_dead(enemy_bullets);
        remove_dead(background_enemy_bullets);
        remove_dead(enemies);
        remove_dead(medals);
        remove_dead(chunks);

        if (stage && stage->next_stage())
                nextStage();
}

void GameState::draw(Graphics &graphics)
{
        graphics.clear();

        if (state_ == State::TITLE_SCREEN) {
                title_screen->draw(graphics);
                graphics.flip();
                return;
        }

        if (stage)
                stage->draw(graphics);
        for (auto &e : background_enemy_bullets)
                e->draw(graphics);
        for (auto &e : enemies)
                e->draw(graphics);
        for (auto &e : medals)
                e.draw(graphics);
        for (auto &e : chunks)
                e.draw(graphics);
        for (auto &e : enemy_bullets)
                e->draw(graphics);
        ship->draw(graphics);
        hud->draw(graphics);
        graphics.flip();
}

void GameState::convertBulletsToMedals()
{
        for (auto &e : background_enemy_bullets)
                medals.push_back({e->position().x, e->position().y});
        for (auto &e : enemy_bullets)
                medals.push_back({e->position().x, e->position().y});

        background_enemy_bullets.clear();
        enemy_bullets.clear();
}

void GameState::nextStage()
{
        switch (state_) {
                case TITLE_SCREEN:
                        state_ = State::STAGE_ONE;
                        stage = std::make_shared<Stage1>();
                        break;
                case STAGE_ONE:
                        state_ = State::STAGE_TWO;
                        stage = std::make_shared<Stage2>();
                        break;
                case STAGE_TWO:
                        state_ = State::GAME_OVER;
                        break;
                default:
                        break;
        }
}
