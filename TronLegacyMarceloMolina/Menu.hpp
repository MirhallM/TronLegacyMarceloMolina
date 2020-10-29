#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include "CScreen.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu : public cScreen
{
private:
	int alpha_div;
	int alpha_max;
	bool jugando;
public:
	Menu(void);

};
#endif // MENU_HPP
