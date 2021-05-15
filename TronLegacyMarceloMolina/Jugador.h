#pragma once
#include <SFML/Graphics.hpp>
#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador
{
private:
	int dir, lives;

public:

	int x, y, speed;
	void tick();
	sf::Color color;
	Jugador(sf::Color, int);
	Jugador(sf::Color _color, int num, int _lives);
	void changeDir(int);
	int getDir();
	int livesLeft();
	void death();
	sf::Vector3f getColor();

};
#endif // !JUGADOR_H