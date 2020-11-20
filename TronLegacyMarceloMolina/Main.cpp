#include <iostream>
#include <SFML\Graphics.hpp>
#include "screens.hpp"

using namespace sf;

int main(int argc, char** argv)
{
	//Vector para almacenar las diferentes escenas
	std::vector<cScreen*> Screens;
	int screen = 0;

	//Crea la ventana con sus dimensiones y titulo
	RenderWindow App(VideoMode(1366, 768), "Tron: Legacy Lights");
	App.setFramerateLimit(60);

	//Hace que el mouse no sea visible en la pantalla
	App.setMouseCursorVisible(false);

	//Preparar las diferentes escenas
	Menu esc0;                //Return 0
	Screens.push_back(&esc0);
	Game esc2;				  //Return 1
	Screens.push_back(&esc2);
	SinglePlayer esc1;
	Screens.push_back(&esc1); //Return 2
	
	//Habilitaciones de multiples ventanas concurrentes
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}


	//La mayoria de esto se correra dentro de las ventanas individuales 
	//******************Legacy SFML Window Opener*************************************
	/*//Corre el programa con tal la ventana siga abierta
	while(App.isOpen())
	{
		//Revisa que todos los eventos de la ventana hayan sido lanzados desde la ultima iteracion del loop
		Event event;
		while (screen >= 0)
		{
			screen = Screens[screen]->Run(App);
			//Cierra la ventana si el evento de cerrar es creado
			if (event.type == Event::Closed)
			{
				App.close();
			}
		}

		//Limpia todos los pixeles con negro 
		//Necesario antes de dibujar otra pantalla
		App.clear(Color::Black);

		//Dibujar todo aqui
		//App.draw(....);

		//Terminar de dibujar el cuadro actual y mostrarlo
		App.display();

	}*/
	return EXIT_SUCCESS;
}