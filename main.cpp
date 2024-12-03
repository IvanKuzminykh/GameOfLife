#include <SFML/Graphics.hpp>
#include "gamefield.h"
#include <iostream>

int main()
{
	for (;;)
	{
		std::cout << "Enter width and height of game field: ";
		ui width, height;
		std::cin >> width >> height;
		sf::RenderWindow w(sf::VideoMode(600, 600), "Game of life");
		GameField game(width, height);
		game.randomInitialization();
		while (w.isOpen())
		{
			sf::Event e;
			while (w.pollEvent(e))
			{
				if (e.type == sf::Event::Closed || e.key.code == sf::Keyboard::Escape)
					w.close();
			}
			w.clear();
			game.drawOnRenderTarget(w);
			game.nextGeneration();
			w.display();
		}
		std::cout << "Window closed.\n";
	}
	return 0;
}
