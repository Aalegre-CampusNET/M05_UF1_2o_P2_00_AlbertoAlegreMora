#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "Enemy.h"
#include <vector>
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };
class Player
{
	COORD direction;
	char character;
	ConsoleUtils::CONSOLE_COLOR background;
	ConsoleUtils::CONSOLE_COLOR foreground;
public:

	COORD spawn;
	COORD position;
	int points = 0;
	int life = 3;
	const int POWERUP_PICKUP = 100;
	Player(COORD _spawn);
	void Update(Map* _map, USER_INPUTS input, std::vector<Enemy>* enemies);
	void Draw();

};

