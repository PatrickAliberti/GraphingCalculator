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

	// Do these need to be members?
	sf::VertexArray XAxis;
	sf::VertexArray YAxis;

	int numOfPoints;
	sf::VertexArray function;

	sf::VertexArray background;

	std::string functionExpression;

public:
	Window(sf::RenderWindow&);
	Window(sf::RenderWindow&, double, double, double, double, std::string);

	void graphFunction();
	void drawTo(sf::RenderWindow&);
};