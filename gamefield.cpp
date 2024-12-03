#include "gamefield.h"
#include <random>
#include <future>
#include <omp.h>

GameField::GameField(ui width, ui height) : 
	_width(width), _height(height)
{
	_field = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));
}

void GameField::nextGeneration()
{
	std::vector<std::future<void>> pool;
	auto newgen = _field;
	for (ui j = 0; j < _height; ++j)
	{
		//pool.push_back(std::async([&]() 
			//{
			for (ui i = 0; i < _width; ++i)
			{
				if (_field[j][i])
				{
					if (aliveNeighboursCount(i, j) < 2 || aliveNeighboursCount(i, j) > 3)
						newgen[j][i] = false;
				}
				else
				{
					if (aliveNeighboursCount(i, j) == 3)
						newgen[j][i] = true;
				}
			}
			/*}));*/
	}
	for (auto& fut : pool) 
		fut.wait();
	_field = newgen;
}

ui GameField::aliveNeighboursCount(ui x, ui y)
{
	auto sum = 0;
	for (ui j = (_height + y - 1) % _height; j <= (_height + y + 1) % _height; ++j)
	{
		for (ui i = (_width + x - 1) % _width; i <= (_width + x + 1) % _width; ++i)
		{
			if (i == x && j == y) continue;
			if (_field[j][i]) ++sum;
		}
	}
	return sum;
}

void GameField::randomInitialization()
{
	std::mt19937 engine(std::time(nullptr));
	for (ui j = 0; j < _height; ++j)
	{
		for (ui i = 0; i < _width; ++i)
		{
			_field[j][i] = (bool)(engine() % 2);
		}
	}
}

void GameField::drawOnRenderTarget(sf::RenderTarget& rt)
{
	auto x_ratio = rt.getSize().x / _width;
	auto y_ratio = rt.getSize().y / _height;
	for (ui j = 0; j < _height; ++j)
	{
		for (ui i = 0; i < _width; ++i)
		{
			sf::RectangleShape cell(sf::Vector2f(x_ratio, y_ratio));
			cell.setPosition(i * x_ratio, j * y_ratio);
			if (_field[j][i])
				cell.setFillColor(sf::Color::White);
			else
				cell.setFillColor(sf::Color::Black);
			rt.draw(cell);
		}
	}
}

const sf::VertexArray GameField::getVertexArray() const
{
	auto vertex_array = sf::VertexArray();
	{
		for (ui j = 0; j < _height; ++j)
		{
			for (ui i = 0; i < _width; ++i)
			{
				if (_field[j][i])
					vertex_array.append(sf::Vertex(sf::Vector2f(i, j), sf::Color(sf::Color::White)));
				else
					vertex_array.append(sf::Vertex(sf::Vector2f(i, j), sf::Color(sf::Color::Black)));
			}
		}
	}
	return vertex_array;
}