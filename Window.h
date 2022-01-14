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
	sf::VertexArray background;
	sf::VertexArray XAxis;
	sf::VertexArray YAxis;
	// sf::VertexArray XTickMars;
	// sf::VertexArray YTickMarks;

	int numOfPoints;
	sf::VertexArray function;

	std::string functionExpression;

public:
	// Constructors
	Window(sf::RenderWindow&);
	Window(sf::RenderWindow&, double, double, double, double, std::string);

	// Accessors
	double getXLowerLimit();
	double getXUpperLimit();
	double getYLowerLimit();
	double getYUpperLimit();

	// Mutators
	void setXLowerLimit(double);
	void setXUpperLimit(double);
	void setYLowerLimit(double);
	void setYUpperLimit(double);

	void graphFunction();
	void drawTo(sf::RenderWindow&);
};