#pragma once
#include "Map.h"
#include "Enemy.h"
#include "TimeManager.h"
#include <vector>
#include "CustomVector.h"
#include "Player.h"
struct AppInfo {
	Map pacman_map = Map();
	std::vector<Enemy> enemies;
	Player player = Player(pacman_map.spawn_player);
	USER_INPUTS input = USER_INPUTS::NONE;
	bool run = true;
	bool win = false;
	bool loose = false;
};