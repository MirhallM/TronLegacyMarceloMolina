#pragma once
#ifndef GAME_H
#define GAME_H

#include "CScreen.hpp"
#include <SFML\Graphics.hpp>

class Game : public cScreen
{
public:
	void respawn();
	void loadArena();
	Game(void);
private:
	virtual int Run(sf::RenderWindow& App);
	void Update(bool& Jugando, bool& Corriendo, sf::Text& Win1, sf::Text& Win2, sf::RenderTexture& t, int& retflag);
	int processEvents(sf::RenderWindow& App, sf::Event& event, bool& retflag, bool& Paused, bool& Corriendo, bool& Jugando, bool& Win);
	void Render(sf::RenderWindow& App, sf::Sprite& sprite);
	void DibujarPausa(sf::RenderWindow& App, sf::Sprite& sprite, sf::Text& PauseText);
	void DibujarWin1(sf::RenderWindow& App, sf::Sprite& spriteMP, sf::Text& Win1);
	void DibujarWin2(sf::RenderWindow& App, sf::Sprite& spriteMP, sf::Text& Win2);
};

#endif // !GAME_H