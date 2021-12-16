#pragma once
#include "ConsoleUtils.h"
#include "Map.h"
#include "Enemy.h"
#include <vector>
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };
class Player
{
	COORD spawn;
	COORD direction;
	char character;
	ConsoleUtils::CONSOLE_COLOR background;
	ConsoleUtils::CONSOLE_COLOR foreground;
public:
	COORD position;
	int points = 0;
	Player(COORD _spawn);
	void Update(Map* _map, USER_INPUTS input, std::vector<Enemy>* enemies);
	void Draw();

};

