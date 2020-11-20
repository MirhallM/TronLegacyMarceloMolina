#include "Jugador.h"
#include <time.h>

void Jugador::tick()
{
	if (dir == 0) y += 1; //Down
	if (dir == 1) x -= 1; //Left
	if (dir == 2) x += 1; //Right
	if (dir == 3) y -= 1; //Up
}

Jugador::Jugador(sf::Color _color, int num) : lives(3)
{
	if (num == 1) 
	{
		x = 1;
		dir = 2;
	}
	else 
	{
		x = 1364;
		dir = 1;
	}

	y = 384;
	color = _color;
	speed = 1;
}

void Jugador::changeDir(int _dir)
{
	this->dir = _dir;
}

int Jugador::getDir()
{
	return dir;
}

int Jugador::livesLeft(Jugador)
{
	return lives;
}

sf::Vector3f Jugador::getColor()
{
	return sf::Vector3f(color.r, color.g, color.b);
}