#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using ui = unsigned int;

class GameField
{
public:
	GameField(ui width, ui height);
	void nextGeneration();
	ui aliveNeighboursCount(ui x, ui y);
	void randomInitialization();
	void drawOnRenderTarget(sf::RenderTarget& rt);
private:
	std::vector<std::vector<bool>> _field;
	ui _width;
	ui _height;
};