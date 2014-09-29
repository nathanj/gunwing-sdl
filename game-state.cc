#include "game-state.h"

#include "utils.h"

// static
Ship* GameState::ship;
std::vector<std::shared_ptr<Sprite>> GameState::enemy_bullets;
std::vector<std::shared_ptr<Sprite>> GameState::enemies;
std::vector<Medal> GameState::medals;
std::vector<EnemyChunk> GameState::chunks;

void GameState::update(std::chrono::milliseconds delta)
{
        for (auto& e : GameState::enemies)
                e->update(delta);
        for (auto& e : GameState::medals)
                e.update(delta);
        for (auto& e : GameState::chunks)
                e.update(delta);
	for (unsigned int i = 0; i < enemy_bullets.size(); ++i)
		enemy_bullets[i]->update(delta);

        remove_dead(GameState::enemy_bullets);
        remove_dead(GameState::enemies);
        remove_dead(GameState::medals);
        remove_dead(GameState::chunks);
}

void GameState::draw(Graphics& graphics)
{
        for (auto& e : GameState::enemies)
                e->draw(graphics);
        for (auto& e : GameState::medals)
                e.draw(graphics);
        for (auto& e : GameState::chunks)
                e.draw(graphics);
        for (auto& e : GameState::enemy_bullets)
                e->draw(graphics);
        ship->draw(graphics);
}
