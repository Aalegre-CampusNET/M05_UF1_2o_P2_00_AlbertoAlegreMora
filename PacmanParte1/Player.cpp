#include "Player.h"

Player::Player(COORD _spawn)
{
	spawn = _spawn;
	position = spawn;
	direction = { 0,0 };
	character = 'O';
	foreground = ConsoleUtils::CONSOLE_COLOR::YELLOW;
	background = ConsoleUtils::CONSOLE_COLOR::BLACK;
}

void Player::Update(Map* _map, USER_INPUTS input, std::vector<Enemy>* enemies)
{
    COORD newPos = position;
    switch (input)
    {
    case UP:
        newPos.Y--;
        break;
    case DOWN:
        newPos.Y++;
        break;
    case RIGHT:
        newPos.X++;
        break;
    case LEFT:
        newPos.X--;
        break;
    }
    if (newPos.X < 0)
    {
        newPos.X = _map->Width - 1;
    }
    newPos.X %= _map->Width;
    if (newPos.Y < 0)
    {
        newPos.Y = _map->Height - 1;
    }
    newPos.Y %= _map->Height;

    switch (_map->GetTile(newPos.X, newPos.Y))
    {
    case Map::MAP_TILES::MAP_WALL:
        newPos.Y = position.Y;
        newPos.X = position.X;
        break;
    case Map::MAP_TILES::MAP_POINT:
        _map->points--;
        points++;
        _map->SetTile(newPos.X, newPos.Y, Map::MAP_TILES::MAP_EMPTY);
        break;
    case Map::MAP_TILES::MAP_POWERUP:
        points += 100;
        _map->SetTile(newPos.X, newPos.Y, Map::MAP_TILES::MAP_EMPTY);
        for (size_t i = 0; i < enemies->size(); i++)
        {
            enemies->at(i).PowerUpPicked();
        }
        break;
    }
    position = newPos;
}

void Player::Draw()
{
	ConsoleUtils::Console_SetPos(position);
	ConsoleUtils::Console_SetColor(foreground, background);
	std::cout << character;
}
