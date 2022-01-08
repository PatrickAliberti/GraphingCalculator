// To-do
//			Change graph color to red 
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
	
	sf::VertexArray XAxis;
	sf::VertexArray YAxis;

	sf::VertexArray function;
	int numOfPoints;

	std::string functionExpression;

public:
	Window(sf::RenderWindow&);
	Window(sf::RenderWindow&, double, double, double, double, std::string);

	void graphAxes();
	void graphFunction();
	void drawTo(sf::RenderWindow&);
};