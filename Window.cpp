// To-Do
//			Implement tick marks/Gridlines
//
//			Instead ofusing numOfPoints, use size() methods
//
//			Make function line thicker
//
//			Accessors and Modifiers
//
//			Go to the bank
#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Window.h"

Window::Window(sf::RenderWindow& window) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = -10;
	XUpperLimit = 10;
	YLowerLimit = -10;
	YUpperLimit = 10;

	background.setPrimitiveType(sf::Quads);
	background.resize(4);
	background[0].position = sf::Vector2f(XOrigin + XLowerLimit * 20, YOrigin + YUpperLimit * 20);
	background[1].position = sf::Vector2f(XOrigin + XUpperLimit * 20, YOrigin + YUpperLimit * 20);
	background[2].position = sf::Vector2f(XOrigin + XUpperLimit * 20, YOrigin + YLowerLimit * 20);
	background[3].position = sf::Vector2f(XOrigin + XLowerLimit * 20, YOrigin + YLowerLimit * 20);
	for (int index = 0; index < 4; index++) {
		background[index].color = sf::Color{ 36, 36, 36 };
	}

	XAxis.setPrimitiveType(sf::Lines);
	XAxis.resize(2);
	YAxis.setPrimitiveType(sf::Lines);
	YAxis.resize(2);
	XAxis[0].position = sf::Vector2f(XOrigin + XLowerLimit * 20, YOrigin);
	XAxis[1].position = sf::Vector2f(XOrigin + XUpperLimit * 20, YOrigin);
	YAxis[0].position = sf::Vector2f(XOrigin, YOrigin + YLowerLimit * 20);
	YAxis[1].position = sf::Vector2f(XOrigin, YOrigin + YUpperLimit * 20);
	for (int index = 0; index < 2; index++) {
		XAxis[index].color = sf::Color{ 105, 105, 105 };
		YAxis[index].color = sf::Color{ 105, 105, 105 };
	}

	// Label Axes

	function.setPrimitiveType(sf::Quads);
	numOfPoints = ((XUpperLimit - XLowerLimit) / .001) * 4;
	function.resize(numOfPoints);
	for (int index = 0; index < numOfPoints; index++) {
		function[index].color = sf::Color::Red;
	}

	functionExpression = "sin(X)";
}

// To-Do
//			Make this constructor do the same as the other
Window::Window(sf::RenderWindow& window, double XLowerLim, double XUpperLim, double YLowerLim, double YUpperLim, std::string fx) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = XLowerLim;
	XUpperLimit = XUpperLim;
	YLowerLimit = YLowerLim;
	YUpperLimit = YUpperLim;

	functionExpression = fx;

	function.setPrimitiveType(sf::Points);

	numOfPoints = ((XUpperLimit - XLowerLimit) / 0.001);
	function.resize(numOfPoints);

	for (int index = 0; index < numOfPoints; index++) {
		function[index].color = sf::Color::Red;
	}
}

// To-Do: 
//			Convert string from user into computer intruction
//			using the muparser library
void Window::graphFunction() {
	double YVal;

	for (double XVal = XLowerLimit, index = 0.0; XVal < XUpperLimit; XVal += 0.001, index += 4) {
		YVal = (XVal*XVal*XVal)-2*XVal;
		if (YVal > YUpperLimit || YVal < YLowerLimit) {
			continue;
		}

		function[index].position = sf::Vector2f((XOrigin + XVal * 20) + 1.f, (YOrigin - YVal * 20) - 1.f);
		function[index + 1].position = sf::Vector2f((XOrigin + XVal * 20) - 1.f, (YOrigin - YVal * 20) - 1.f);
		function[index + 2].position = sf::Vector2f((XOrigin + XVal * 20) - 1.f, (YOrigin - YVal * 20) + 1.f);
		function[index + 3].position = sf::Vector2f((XOrigin + XVal * 20) + 1.f, (YOrigin - YVal * 20) + 1.f);
	}
}

void Window::drawTo(sf::RenderWindow& window) {
	window.draw(background);

	window.draw(XAxis);
	window.draw(YAxis);
	
	window.draw(function);
}