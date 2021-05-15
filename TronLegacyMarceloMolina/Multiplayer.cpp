#include "Game.hpp"
#include <time.h>
#include "Jugador.h"
#include <iostream>

using namespace sf;

Jugador p1(Color::Blue, 1);
Jugador p2(Color::Red, 2);
const int W = 1366, H = 768;
bool Arena[W][H] = { 0 };
Sprite spriteMP;
RenderTexture tex;
int speed = 4;
int winner = 0;
bool Win;

void Game::respawn()
{
	loadArena();
	tex.create(W, H);
	tex.setSmooth(true);
	spriteMP.setTexture(tex.getTexture());
	tex.clear();
	Texture texture;
	texture.loadFromFile("Resources/grid-background.png");
	Sprite escBackground(texture);
	tex.draw(escBackground);
	p1 = Jugador(Color::Blue, 1);
	p2 = Jugador(Color::Red, 2);

}

void Game::loadArena()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			Arena[i][j] = 0;
		}
	}
	for (int i = 0; i < W; i++)
	{
		Arena[i][0] = 1;
		Arena[i][H - 1] = 1;
	}
	for (int i = 0; i < H; i++)
	{
		Arena[0][i] = 1;
		Arena[W - 1][i] = 1;
	}
}

Game::Game(void)
{
}

int Game::Run(RenderWindow& App)
{
	Texture texture;
	texture.loadFromFile("Resources/grid-background.png");
	Sprite escBackground(texture);
	
	tex.create(W, H);
	tex.setSmooth(true);
	spriteMP.setTexture(tex.getTexture());
	tex.clear();
	tex.draw(escBackground);

	Font Font;
	Text Win1;
	Text Win2;

	Text PauseText;
	sf::Font PauseFont;

	if (!PauseFont.loadFromFile("Resources/verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}
	PauseText.setFont(PauseFont);
	PauseText.setCharacterSize(48);
	PauseText.setString("     GAME PAUSED\n   Press P to Continue\nPress Enter to exit to Menu");
	PauseText.setPosition(W / 4, H / 3);


	Win1.setFont(PauseFont);
	Win1.setCharacterSize(48);
	Win1.setString("     Blue Player Wins\n   Press P to Continue\nPress Enter to exit to Menu");
	Win1.setPosition(W / 4, H / 3);
	

	Win2.setFont(PauseFont);
	Win2.setCharacterSize(48);
	Win2.setString("     Red Player Wins\n   Press P to Continue\nPress Enter to exit to Menu");
	Win2.setPosition(W / 4, H / 3);

	//Reload arena to make sure all positions are empty
	loadArena();
	respawn();

	Win = 0;
	bool Corriendo = 1;
	bool Jugando = 1;
	bool Paused = 0;
	winner = 0;
	Event event;

	//Aqui comienza el proceso viejo de crear la escena
	while (Corriendo)
	{
		bool retflag;
		int retval = processEvents(App, event, retflag, Paused, Corriendo, Jugando, Win);
		if (retflag) return retval;
		
		if(!Paused && !Win)
		{ 
			int retflag2;
			Update(Jugando, Corriendo, Win1, Win2, tex, retflag2);
			if (retflag2 == 3) continue;

			////PROCESO DE 3 PASOS: CLEAR/DRAW/DISPLAY
			Render(App, spriteMP);
		}
		else if (Win)
		{
			switch (winner)
			{
			case 1:
				DibujarWin1(App, spriteMP, Win1);
				break;
			case 2:
				DibujarWin2(App, spriteMP, Win2);
				break;
			}
		}
		else if(Paused)
		{
			DibujarPausa(App, spriteMP, PauseText);
		}
	}

	return 0;
}

void Game::Update(bool& Jugando, bool& Corriendo, sf::Text& Win1, sf::Text& Win2, sf::RenderTexture& tex, int& retflag)
{
	retflag = 1;
	//Si el juego termino el ultimo frame, salir
	if (!Jugando) {
		loadArena();
		Corriendo = 0;
		{ retflag = 3; return; };
	}

	//Seguir corriendo el juego y verificar si debe continuar
	//Se hara en una sola funcion que ambos comparten
	for (int i = 0; i < 4; i++)
	{
		p1.tick();
		p2.tick();
		int colision = 0;
		if (Arena[p1.x][p1.y] == 1) winner = 2;
		else if (Arena[p2.x][p2.y] == 1) winner = 1;
		if (winner != 0)
		{
			Win = 1;
			loadArena();
		}
		else
		{
			Arena[p1.x][p1.y] = 1;
			Arena[p2.x][p2.y] = 1;

			CircleShape c(3);
			c.setPosition((float)p1.x, (float)p1.y); c.setFillColor(p1.color); tex.draw(c);
			c.setPosition((float)p2.x, (float)p2.y); c.setFillColor(p2.color); tex.draw(c);
			tex.display();
		}
	}
}

int Game::processEvents(sf::RenderWindow& App, sf::Event& event, bool& retflag, bool& Paused, bool& Corriendo, bool& Jugando, bool& Win)
{
	retflag = true;
	//Verificar eventos
	while (App.pollEvent(event))
	{
		//Si se cierra la ventana
		if (event.type == Event::Closed)
		{
			App.close();
			return (-1);
		}
	}
	//Control de teclas presionadas
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (p1.getDir() != 2)
			p1.changeDir(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (p1.getDir() != 1)
			p1.changeDir(2);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (p1.getDir() != 0)
			p1.changeDir(3);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (p1.getDir() != 3)
			p1.changeDir(0);
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		if (p2.getDir() != 2)
			p2.changeDir(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		if (p2.getDir() != 1)
			p2.changeDir(2);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (p2.getDir() != 0)
			p2.changeDir(3);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		if (p2.getDir() != 3)
			p2.changeDir(0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		if (!Paused)
			Paused = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::P))
	{
		if (Paused)
			Paused = 0;
		else if (Win)
		{
			Win = 0;
			winner = 0;
			respawn();
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		if (Paused || Win)
		{
			Jugando = 0;
			Corriendo = 0;
		}
	}
	retflag = false;
	return {};
}

void Game::Render(sf::RenderWindow& App, sf::Sprite& spriteMP)
{
	App.clear();
	App.draw(spriteMP);
	App.display();
}

void Game::DibujarPausa(sf::RenderWindow& App, sf::Sprite& spriteMP, sf::Text& PauseText)
{
	App.clear();
	App.draw(spriteMP);
	App.draw(PauseText);
	App.display();
}

void Game::DibujarWin1(sf::RenderWindow& App, sf::Sprite& spriteMP, sf::Text& Win1)
{
	App.clear();
	App.draw(spriteMP);
	App.draw(Win1);
	App.display();
}

void Game::DibujarWin2(sf::RenderWindow& App, sf::Sprite& spriteMP, sf::Text& Win2)
{
	App.clear();
	App.draw(spriteMP);
	App.draw(Win2);
	App.display();
}