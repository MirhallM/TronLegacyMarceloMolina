#include "Game.hpp"
#include <time.h>
#include "Jugador.h"
#include <iostream>

using namespace sf;


const int W = 1366, H = 768;
bool Arena[W][H] = { 0 };
int speed = 4;

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

	Jugador p1(Color::Blue, 1);
	Jugador p2(Color::Red, 2);

	Sprite sprite;
	RenderTexture t;
	t.create(W, H);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	t.draw(escBackground);

	Font Font;
	Text Win1;
	Text Win2;

	if (!Font.loadFromFile("Resources/verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	//Blue Player 1 Wins!
	Win1.setFont(Font);
	Win1.setCharacterSize(72);
	Win1.setString("Blue Player Wins");
	Win1.setPosition(W / 2, H / 2 + 40);
	
	//Red Player 2 Wins!
	Win2.setFont(Font);
	Win2.setCharacterSize(72);
	Win2.setString("Red Player Wins");
	Win2.setPosition(W / 2, H / 2 + 40);

	//Reload arena to make sure all positions are empty
	loadArena();

	bool Corriendo = 1;
	bool Jugando = 1;
	Event event;

	//Aqui comienza el proceso viejo de crear la escena
	while (Corriendo)
	{
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

		//Si el juego termino el ultimo frame, salir
		if (!Jugando) {
			loadArena();
			Corriendo = 0;
			continue;
		}

		//Seguir corriendo el juego y verificar si debe continuar
		//Se hara en una sola funcion que ambos comparten
		for (int i = 0; i < speed; i++)
		{
			p1.tick(); p2.tick();
			if (Arena[p1.x][p1.y] == 1)
			{
				Win1.setFillColor(p2.color);
				Jugando = 0;
			}
			if (Arena[p2.x][p2.y] == 1) 
			{
				Win2.setFillColor(p2.color);
				Jugando = 0;
			}
			Arena[p1.x][p1.y] = 1;
			Arena[p2.x][p2.y] = 1;

			CircleShape c(3);
			c.setPosition((float)p1.x, (float)p1.y); c.setFillColor(p1.color); t.draw(c);
			c.setPosition((float)p2.x, (float)p2.y); c.setFillColor(p2.color); t.draw(c);
			t.display();
		}
		////PROCESO DE 3 PASOS: CLEAR/DRAW/DISPLAY
		App.clear();
		App.draw(sprite);
		App.display();
	}

	return 0;
}