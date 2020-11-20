#pragma once
#include "Jugador.h"
#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "CScreen.hpp"
#include <SFML\Graphics.hpp>

class SinglePlayer : public cScreen
{
public:
	void loadArena();
	SinglePlayer(void);
	virtual int Run(sf::RenderWindow& App);
	void DibujarPausa(sf::RenderWindow& App, sf::Sprite& sprite, sf::Text& PauseText);
	int Events(sf::RenderWindow& App, sf::Event& event, bool& retflag);
	void DibujarMundo(sf::RenderWindow& App, sf::Sprite& sprite);
	void UpdateGame(Jugador& p1, bool& Jugando, sf::RenderTexture& t);
	int GameEnded(bool Jugando, bool& Corriendo, bool& retflag);
	void Inputs(Jugador& p1, bool& Paused, bool& Corriendo, bool& Jugando);
};

#endif // !GAME_H