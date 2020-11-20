#include "SinglePlayer.h"
#include <time.h>
#include "Jugador.h"
#include "Enemigo.h"
#include <iostream>
using namespace sf;

const int W = 1366, H = 768;
bool Field[W][H] = { 0 };

void SinglePlayer::loadArena()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			Field[i][j] = 0;
		}
	}
	for (int i = 0; i < W; i++)
	{
		Field[i][0] = 1;
		Field[i][H - 1] = 1;
	}
	for (int i = 0; i < H; i++)
	{
		Field[0][i] = 1;
		Field[W - 1][i] = 1;
	}
}

SinglePlayer::SinglePlayer(void)
{
}

int SinglePlayer::Run(RenderWindow& App)
{
	Texture texture;
	texture.loadFromFile("Resources/grid-background.png");
	Sprite escBackground(texture);

	int Level = 1;
	Jugador p1(Color::Blue, 1);
	Enemigo e1(1);
	Enemigo e2(2);
	Enemigo e3(3);

	Text PauseText;
	Font PauseFont;
	if (!PauseFont.loadFromFile("Resources/verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}
	PauseText.setFont(PauseFont);
	PauseText.setCharacterSize(48);
	PauseText.setString("     GAME PAUSED\n   Press P to Continue\nPress Enter to exit to Menu");
	PauseText.setPosition(W / 4, H / 3);

	Sprite sprite;
	RenderTexture t;
	t.create(W, H);
	t.setSmooth(true);
	sprite.setTexture(t.getTexture());
	t.clear();
	t.draw(escBackground);

	//Reload arena to make sure all positions are empty
	loadArena();

	bool Corriendo = 1;
	bool Jugando = 1;
	bool Paused = 0;
	Event event;

	//Aqui comienza el proceso viejo de crear la escena
	while (Corriendo)
	{
		//Eventos y Inputs de Teclado
		bool retflag1;
		int retval1 = Events(App, event, retflag1);
		if (retflag1) return retval1;
		Inputs(p1, Paused, Jugando, Corriendo);


		bool retflag2;
		int retval2 = GameEnded(Jugando, Corriendo, retflag2);
		if (retflag2) return retval2;
		if (!Paused)
		{
			UpdateGame(p1, Jugando, t);
			DibujarMundo(App, sprite);
		}
		else
		{
			DibujarPausa(App, sprite, PauseText);
		}
	}
	return 0;
}

void SinglePlayer::DibujarPausa(sf::RenderWindow& App, sf::Sprite& sprite, sf::Text& PauseText)
{
	App.clear();
	App.draw(sprite);
	App.draw(PauseText);
	App.display();
}

int SinglePlayer::Events(sf::RenderWindow& App, sf::Event& event, bool& retflag)
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
	retflag = false;
	return {};
}

void SinglePlayer::DibujarMundo(sf::RenderWindow& App, sf::Sprite& sprite)
{
	////PROCESO DE 3 PASOS: CLEAR/DRAW/DISPLAY
	App.clear();
	App.draw(sprite);
	App.display();
}

void SinglePlayer::UpdateGame(Jugador& p1, bool& Jugando, sf::RenderTexture& t)
{
	//Seguir corriendo el juego y verificar si debe continuar
	//Se hara en una sola funcion que ambos comparten
	for (int i = 0; i < p1.speed; i++)
	{
		p1.tick();
		if (Field[p1.x][p1.y] == 1) Jugando = 0;

		Field[p1.x][p1.y] = 1;

		CircleShape c(3);
		c.setPosition((float)p1.x, (float)p1.y); c.setFillColor(p1.color); t.draw(c);
		t.display();
	}
}

int SinglePlayer::GameEnded(bool Jugando, bool& Corriendo, bool& retflag)
{
	retflag = true;
	//Si el juego termino el ultimo frame, salir
	if (!Jugando) {
		Corriendo = 0;
		return 0;
	}
	retflag = false;
	return {};
}

void SinglePlayer::Inputs(Jugador& p1, bool& Paused, bool& Corriendo, bool& Jugando)
{
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
		if (p1.getDir() != 2)
			p1.changeDir(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		if (p1.getDir() != 1)
			p1.changeDir(2);
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (p1.getDir() != 0)
			p1.changeDir(3);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		if (p1.getDir() != 3)
			p1.changeDir(0);
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
	}
	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		if (Paused)
		{
			Jugando = 0;
			Corriendo = 0;
		}
	}
}
