#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Window.h"

/**
* Contructor
* 
* Sets the origin to the center of the screen, sets the minimum X and Y values to -10, and the maximum X and Y values to 10, and sets the function to sine.
*/
Window::Window(sf::RenderWindow& window) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = -10;
	XUpperLimit = 10;
	YLowerLimit = -10;
	YUpperLimit = 10;

	functionExpression = "sin(X)";

	function.setPrimitiveType(sf::Points);

	numOfPoints = (XUpperLimit - XLowerLimit) / 0.1;
	function.resize(numOfPoints);
}

/**
* Contructor
*
* Sets the instance variables equal to the correspoding argument that is passed through the contructor
*/
Window::Window(sf::RenderWindow& window, double XLowerLim, double XUpperLim, double YLowerLim, double YUpperLim, std::string fx) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = XLowerLim;
	XUpperLimit = XUpperLim;
	YLowerLimit = YLowerLim;
	YUpperLimit = YUpperLim;

	functionExpression = fx;

	function.setPrimitiveType(sf::Points);

	numOfPoints = (XUpperLimit - XLowerLimit) / 0.1;
	function.resize(numOfPoints);
}

// TO-DO: 
//			Figure out how to convert string from user into computer intruction?
void Window::graph() {
	double YVal;

	for (double XVal = XLowerLimit; XVal < XUpperLimit; XVal += 0.1) {
		YVal = sin(XVal);

		int index = (XVal - XLowerLimit) * 10;
		function[index].position = sf::Vector2f(XOrigin + XVal*10, YOrigin + YVal*10);
	}
}

void Window::drawTo(sf::RenderWindow& window) {
	window.draw(function);
}