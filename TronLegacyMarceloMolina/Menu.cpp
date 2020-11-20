#include "Menu.hpp"
#include <iostream>

Menu::Menu(void) : alpha_max(3 * 255), alpha_div(3), jugando{ 0 }
{
}

int Menu::Run(RenderWindow& App)
{
	{
	sf::Event Event;
	bool Running = true;
	sf::Texture TronLogo;
	sf::Sprite Logo;
	sf::Texture Texture;
	sf::Sprite Sprite;
	int alpha = 0;
	sf::Font Font;
	sf::Text MenuSingleplayer;
	sf::Text MenuMultiplayer;
	sf::Text Exit;
	sf::Text MenuAgain;
	sf::Text MenuReturn;
	sf::Text MenuStats;
	int menu = 0;
	if (jugando)
		menu = 1;

	//Cargar el background y el font
	if (!Texture.loadFromFile("Resources/tron.jpg"))
	{
		std::cerr << "Error loading presentation.gif" << std::endl;
		return (-1);
	}
	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, alpha));
	if (!Font.loadFromFile("Resources/verdanab.ttf"))
	{
		std::cerr << "Error loading verdanab.ttf" << std::endl;
		return (-1);
	}

	//SinglePlayer
	MenuSingleplayer.setFont(Font);
	MenuSingleplayer.setCharacterSize(32);
	MenuSingleplayer.setString("Single Player");
	MenuSingleplayer.setPosition({ 90.f, 160.f });

	//Multiplayer
	MenuMultiplayer.setFont(Font);
	MenuMultiplayer.setCharacterSize(32);
	MenuMultiplayer.setString("Multiplayer");
	MenuMultiplayer.setPosition({ 90.f, 220.f });

	//Stats
	MenuStats.setFont(Font);
	MenuStats.setCharacterSize(32);
	MenuStats.setString("Estadisticas");
	MenuStats.setPosition({ 90.f, 280.f });
	
	//Exit
	Exit.setFont(Font);
	Exit.setCharacterSize(32);
	Exit.setString("Exit");
	Exit.setPosition({ 90.f, 340.f });

	//Return to Main Menu
	MenuReturn.setFont(Font);
	MenuReturn.setCharacterSize(32);
	MenuReturn.setString("Main Menu");
	MenuReturn.setPosition({ 90.f, 280.f });

	//Play Again (while playing)
	MenuAgain.setFont(Font);
	MenuAgain.setCharacterSize(32);
	MenuAgain.setString("Play Again");
	MenuAgain.setPosition({ 90.f, 220.f });

	if (jugando)
	{
		alpha = alpha_max;
	}

	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
					if (!jugando)
					{
						if (menu == 0)
							menu = 3;
						else
							menu--;
					}
					else {
						menu = 1;
					}
					break;
				case sf::Keyboard::Down:
					if (!jugando)
					{
						if (menu == 3)
							menu = 0;
						else
							menu++;
					}
					else
						menu = 2;
					break;
				case sf::Keyboard::Return:
					if (!jugando)
					{
						if (menu == 0)
						{
							//Single Player
							jugando = true;
							return (2);
						}
						else if (menu == 1)
						{
							//Multiplayer
							jugando = true;
							return (1);
						}
						else
						{
							//Bye bye!..
							return (-1);
						}
					}
					else
					{
						if (menu == 1)
						{
							//Play again 
							return 1;
						}
						else
						{
							//Main Menu
							jugando = 0;
							return 0;
						}
						
					}
					break;
				default:
					break;
				}
			}
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha<alpha_max)
		{
			alpha++;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
		if (menu == 0)
		{
			MenuSingleplayer.setFillColor(sf::Color(255, 0, 0, 255));
			MenuMultiplayer.setFillColor(sf::Color(255, 255, 255, 255));
			Exit.setFillColor(sf::Color(255, 255, 255, 255));
			MenuStats.setFillColor(sf::Color(255, 255, 255, 255));
			MenuAgain.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else if (menu == 1)
		{
			MenuReturn.setFillColor(sf::Color(255, 255, 255, 255));
			MenuSingleplayer.setFillColor(sf::Color(255, 255, 255, 255));
			MenuMultiplayer.setFillColor(sf::Color(255, 0, 0, 255));
			Exit.setFillColor(sf::Color(255, 255, 255, 255));
			MenuStats.setFillColor(sf::Color(255, 255, 255, 255));
			MenuAgain.setFillColor(sf::Color(255, 0, 0, 255));
		}
		else if (menu == 2)
		{
			MenuReturn.setFillColor(sf::Color(255, 0, 0, 255));
			MenuSingleplayer.setFillColor(sf::Color(255, 255, 255, 255));
			MenuMultiplayer.setFillColor(sf::Color(255, 255, 255, 255));
			Exit.setFillColor(sf::Color(255, 255, 255, 255));
			MenuStats.setFillColor(sf::Color(255, 0, 0, 255));
			MenuAgain.setFillColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			MenuReturn.setFillColor(sf::Color(255, 0, 0, 255));
			MenuSingleplayer.setFillColor(sf::Color(255, 255, 255, 255));
			MenuMultiplayer.setFillColor(sf::Color(255, 255, 255, 255));
			Exit.setFillColor(sf::Color(255, 0, 0, 255));
			MenuStats.setFillColor(sf::Color(255, 255, 255, 255));
			MenuAgain.setFillColor(sf::Color(255, 255, 255, 255));
		}

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
		if (alpha == alpha_max)
		{
			if (jugando)
			{
				App.draw(MenuReturn);
				App.draw(MenuAgain);
			}
			else
			{
				App.draw(MenuSingleplayer);
				App.draw(MenuMultiplayer);
				App.draw(MenuStats);
				App.draw(Exit);
			}
		}
		//Display the results
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}
}
