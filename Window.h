#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

class Window {
private:
	double XOrigin;
	double YOrigin;

	double XLowerLimit;
	double XUpperLimit;
	double YLowerLimit;
	double YUpperLimit;

	std::string functionExpression;

	sf::VertexArray function;
	int numOfPoints;

public:
	Window(sf::RenderWindow&);
	Window(sf::RenderWindow&, double, double, double, double, std::string);

	void graph();
	void drawTo(sf::RenderWindow&);
};