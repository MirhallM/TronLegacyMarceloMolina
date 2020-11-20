#pragma once
#ifndef GAME_H
#define GAME_H

#include "CScreen.hpp"
#include <SFML\Graphics.hpp>

class Game : public cScreen
{
public:
	void loadArena();
	Game(void);
	virtual int Run(sf::RenderWindow& App);
};

#endif // !GAME_H