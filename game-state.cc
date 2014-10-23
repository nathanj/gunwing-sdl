#include "game-state.h"

#include "utils.h"
#include "stage1.h"
#include "stage2.h"
#include "text.h"

// static
std::shared_ptr<Ship> GameState::ship;
std::shared_ptr<Hud> GameState::hud;
std::shared_ptr<Stage> GameState::stage;
std::shared_ptr<TitleScreen> GameState::title_screen;
std::shared_ptr<HighScoreHandler> GameState::high_score_handler;
std::shared_ptr<ChoosePilot> GameState::choose_pilot;
std::vector<std::shared_ptr<Sprite>> GameState::background_enemy_bullets;
std::vector<std::shared_ptr<Sprite>> GameState::enemy_bullets;
std::vector<std::shared_ptr<Sprite>> GameState::enemies;
std::vector<Medal> GameState::medals;
std::vector<EnemyChunk> GameState::chunks;
GameState::State GameState::state_{GameState::State::TITLE_SCREEN};

void GameState::initialize()
{
        title_screen = std::make_shared<TitleScreen>();
        ship = std::make_shared<Ship>();
        hud = std::make_shared<Hud>();
}

void GameState::handleInput(const Input &input)
{
        switch (state_) {
        case TITLE_SCREEN:
                if (input.wasKeyPressed(SDLK_SPACE) ||
                    input.wasButtonPressed(0))
                        nextStage();
                return;
        case CHOOSE_PILOT:
                choose_pilot->handleInput(input);
                return;
        case HIGH_SCORE:
                high_score_handler->handleInput(input);
                return;
        default:
                ship->handleInput(input);
                break;
        }
}

void GameState::update(std::chrono::milliseconds delta)
{
        if (state_ == State::TITLE_SCREEN) {
                title_screen->update(delta);
                return;
        } else if (state_ == State::CHOOSE_PILOT) {
                choose_pilot->update(delta);
                if (choose_pilot->finished()) {
                        ship->type(choose_pilot->selection());
                        nextStage();
                }
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
        } else if (state_ == State::CHOOSE_PILOT) {
                choose_pilot->draw(graphics);
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
        Text::drawString(graphics, "HELLO", 100, 100);
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
                state_ = State::CHOOSE_PILOT;
                choose_pilot = std::make_shared<ChoosePilot>();
                break;
        case CHOOSE_PILOT:
                state_ = State::STAGE_ONE;
                stage = std::make_shared<Stage1>();
                break;
        case STAGE_ONE:
                state_ = State::STAGE_TWO;
                stage = std::make_shared<Stage2>();
                break;
        case STAGE_TWO:
                state_ = State::HIGH_SCORE;
                stage.reset();
                high_score_handler = std::make_shared<HighScoreHandler>();
                break;
        default:
                break;
        }
}
