#pragma once

#include "ship.h"
#include "bullet.h"
#include "sprite.h"
#include "medal.h"
#include "enemy-chunk.h"
#include "graphics.h"

#include <vector>
#include <memory>
#include <chrono>

class GameState {
public:
	static Ship* ship;
	static std::vector<std::shared_ptr<Sprite>> enemy_bullets;
	static std::vector<std::shared_ptr<Sprite>> enemies;
	static std::vector<Medal> medals;
	static std::vector<EnemyChunk> chunks;

        static void update(std::chrono::milliseconds delta);
        static void draw(Graphics& graphics);
};
