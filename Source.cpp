#include <SFML/Graphics.hpp>
#include<iostream>
#include"maze.h"
using namespace sf;
int main()
{
	RenderWindow window(sf::VideoMode(843, 900), "SFML works!");
	maze maz;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		maz.display(window);
		window.display();
	}

	return 0;
}