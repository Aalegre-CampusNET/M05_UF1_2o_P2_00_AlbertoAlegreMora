#include "AppInfo.h"

/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();

AppInfo info;

int main()
{
    Setup();
    while (info.run)
    {
        Input();
        Logic();
        Draw();
    }
}

void Setup()
{
    std::cout.sync_with_stdio(false);

    srand(time(NULL));

    int totalEnemies = 0;
    std::cout << "Cuantos enemigos quieres? ";
    std::cin >> totalEnemies;
    if (totalEnemies < 1)
        totalEnemies = 1;
    for (size_t i = 0; i < totalEnemies; i++)
    {
        info.enemies.push_back(Enemy(info.pacman_map.spawn_enemy, 5.0f * i));
    }

}

void Input()
{
    info.input = USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        info.input = USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        info.input = USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        info.input = USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        info.input = USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        info.input = USER_INPUTS::QUIT;
    }
}

void Logic()
{
    if (info.win || info.loose)
    {
        switch (info.input)
        {
        case QUIT:
            info.run = false;
            break;
        }
    }
    else
    {

        switch (info.input)
        {
        case QUIT:
            info.run = false;
            break;
        }

        info.player.Update(&info.pacman_map, info.input, &info.enemies);

        if (info.pacman_map.points <= 0)
        {
            info.win = true;
        }


        for (size_t i = 0; i < info.enemies.size(); i++)
        {
            switch (info.enemies[i].Update(&info.pacman_map, info.player.position))
            {
            case Enemy::ENEMY_STATE::ENEMY_EATED:
                info.player.position = info.player.spawn;
                info.player.life--;
                break;
            case Enemy::ENEMY_STATE::ENEMY_KILLED:
                info.enemies[i].Kill();
                info.player.points += 50;
                break;
            default:
                break;
            }
        }
        if (info.player.life <= 0) {
            info.loose = true;
        }
    }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0,0);
    info.pacman_map.Draw();

    info.player.Draw();
    for (size_t i = 0; i < info.enemies.size(); i++)
    {
        info.enemies[i].Draw();
    }
    ConsoleUtils::Console_ClearCharacter({ 0,(short)info.pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << info.player.points << " Puntuacion pendiente: " << info.pacman_map.points << std::endl;
    if (info.win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
    }
    if (info.loose)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::RED);
        std::cout << "Has perdido!" << std::endl;
    }

    std::cout << TimeManager::getInstance().frameCount << std::endl;
    std::cout << TimeManager::getInstance().deltaTime << std::endl;
    std::cout << TimeManager::getInstance().time << std::endl;

    TimeManager::getInstance().NextFrame();
}