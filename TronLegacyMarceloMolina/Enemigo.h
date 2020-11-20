#pragma once
#include <SFML/Graphics.hpp>
#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo
{
private:
	int speed;
public:
	int x, y, dir;
	void tick();
	sf::Color color;
	Enemigo(int);
	sf::Vector3f getColor();
	void increaseSpeedLevel();

};
#endif // !ENEMIGO_H
