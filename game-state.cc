#include "game-state.h"

#include "utils.h"

// static
Ship* GameState::ship;
Hud* GameState::hud;
std::vector<std::shared_ptr<Sprite>> GameState::enemy_bullets;
std::vector<std::shared_ptr<Sprite>> GameState::enemies;
std::vector<Medal> GameState::medals;
std::vector<EnemyChunk> GameState::chunks;

void GameState::update(std::chrono::milliseconds delta)
{
        for (auto& e : enemies)
                e->update(delta);
        for (auto& e : medals)
                e.update(delta);
        for (auto& e : chunks)
                e.update(delta);
	for (unsigned int i = 0; i < enemy_bullets.size(); ++i)
		enemy_bullets[i]->update(delta);

        remove_dead(enemy_bullets);
        remove_dead(enemies);
        remove_dead(medals);
        remove_dead(chunks);
}

void GameState::draw(Graphics& graphics)
{
        for (auto& e : enemies)
                e->draw(graphics);
        for (auto& e : medals)
                e.draw(graphics);
        for (auto& e : chunks)
                e.draw(graphics);
        for (auto& e : enemy_bullets)
                e->draw(graphics);
        ship->draw(graphics);
        hud->draw(graphics);
}

void GameState::convertBulletsToMedals()
{
	for (auto& e : enemy_bullets)
		medals.push_back( {e->position().x, e->position().y} );

	enemy_bullets.clear();
}
