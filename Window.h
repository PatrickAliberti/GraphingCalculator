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

	double XScale;
	double YScale;

	sf::VertexArray background;
	sf::VertexArray XAxis;
	sf::VertexArray YAxis;
	sf::VertexArray XTickMarks;
	sf::VertexArray YTickMarks;

	sf::VertexArray function;

	std::string functionExpression;

	void setWindow();

public:
	// Constructors
	Window(sf::RenderWindow&);
	Window(sf::RenderWindow&, double, double, double, double, double, double);

	// Mutators
	void setXLowerLimit(double);
	void setXUpperLimit(double);
	void setYLowerLimit(double);
	void setYUpperLimit(double);

	// Accessors
	double getXLowerLimit();
	double getXUpperLimit();
	double getYLowerLimit();
	double getYUpperLimit();

	void graphFunction(sf::RenderWindow&);
	void drawTo(sf::RenderWindow&);
};