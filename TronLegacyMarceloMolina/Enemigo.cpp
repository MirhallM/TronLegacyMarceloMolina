#include "Enemigo.h"
#include "Game.hpp"

void Enemigo::tick()
{
    if (dir == 0) y += 1;
    if (dir == 1) x -= 1;
    if (dir == 2) x += 1;
    if (dir == 3) y -= 1;
}

Enemigo::Enemigo(int num)
{
    srand(time(0));
    if (num == 1)
    {
        color = sf::Color::Green;
    }
    else if (num == 2)
    {
        color = sf::Color(255, 165, 0, 255);
    }
    else if (num == 3)
    {
        color = sf::Color(128, 0, 128, 255);
    }

    x = rand() % 1366;
    y = rand() % 768;
    speed = 1;
    dir = rand() % 4;
}

sf::Vector3f Enemigo::getColor()
{
    return sf::Vector3f();
}

void Enemigo::increaseSpeedLevel()
{
}
