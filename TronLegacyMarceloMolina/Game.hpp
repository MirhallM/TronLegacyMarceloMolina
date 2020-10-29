#pragma once
#ifndef GAME_H
#define GAME_H

#include "CScreen.hpp"
#include <SFML\Graphics.hpp>

struct jugador
{
	unsigned int x, y, dir;
	void tick();
	jugador(sf::Color);

	sf::Vector3f getColor();
};

class Game : public cScreen
{
private:
	const int W = 600, H = 480;
	int speed;
	bool jugando;
public:
	Game(void);
	virtual int Run(sf::RenderWindow& App);
};

#endif // !GAME_H