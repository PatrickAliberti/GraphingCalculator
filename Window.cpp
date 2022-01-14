// To-Do
//			Implement tick marks/Gridlines
//
//			Have a menu screen where the user sets the upper and lower limits for the axes and the allows user to graph multiple different functions

#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Window.h"

// Constructors
Window::Window(sf::RenderWindow& window) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = -20;
	XUpperLimit = 20;
	YLowerLimit = -20;
	YUpperLimit = 20;

	background.setPrimitiveType(sf::Quads);
	background.resize(4);
	background[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 20, YOrigin + 2 + YUpperLimit * 20);
	background[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 20, YOrigin + 2 + YUpperLimit * 20);
	background[2].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 20, YOrigin - 2 + YLowerLimit * 20);
	background[3].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 20, YOrigin - 2 + YLowerLimit * 20);
	for (int index = 0; index < 4; index++) {
		background[index].color = sf::Color{ 36, 36, 36 };
	}

	XAxis.setPrimitiveType(sf::Lines);
	XAxis.resize(2);
	YAxis.setPrimitiveType(sf::Lines);
	YAxis.resize(2);
	XAxis[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 20, YOrigin);
	XAxis[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 20, YOrigin);
	YAxis[0].position = sf::Vector2f(XOrigin, YOrigin - 2 + YLowerLimit * 20);
	YAxis[1].position = sf::Vector2f(XOrigin, YOrigin + 2 + YUpperLimit * 20);
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

Window::Window(sf::RenderWindow& window, double XLowerLim, double XUpperLim, double YLowerLim, double YUpperLim, std::string fx) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = XLowerLim;
	XUpperLimit = XUpperLim;
	YLowerLimit = YLowerLim;
	YUpperLimit = YUpperLim;

	background.setPrimitiveType(sf::Quads);
	background.resize(4);
	background[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 20, YOrigin + 2 + YUpperLimit * 20);
	background[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 20, YOrigin + 2 + YUpperLimit * 20);
	background[2].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 20, YOrigin - 2 + YLowerLimit * 20);
	background[3].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 20, YOrigin - 2 + YLowerLimit * 20);
	for (int index = 0; index < 4; index++) {
		background[index].color = sf::Color{ 36, 36, 36 };
	}

	XAxis.setPrimitiveType(sf::Lines);
	XAxis.resize(2);
	YAxis.setPrimitiveType(sf::Lines);
	YAxis.resize(2);
	XAxis[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 20, YOrigin);
	XAxis[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 20, YOrigin);
	YAxis[0].position = sf::Vector2f(XOrigin, YOrigin - 2 + YLowerLimit * 20);
	YAxis[1].position = sf::Vector2f(XOrigin, YOrigin + 2 + YUpperLimit * 20);
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
}

// Accessors
double Window::getXLowerLimit() {
	return XLowerLimit;
}

double Window::getXUpperLimit() {
	return XUpperLimit;
}

double Window::getYLowerLimit() {
	return YLowerLimit;
}

double Window::getYUpperLimit() {
	return YUpperLimit;
}

// Mutators
void Window::setXLowerLimit(double XLowLim) {
	XLowerLimit = XLowLim;
}

void Window::setXUpperLimit(double XUppLim) {
	XUpperLimit = XUppLim;
}

void Window::setYLowerLimit(double YLowLim) {
	YLowerLimit = YLowLim;
}

void Window::setYUpperLimit(double XUppLim) {
	XUpperLimit = XUppLim;
}

// To-Do: 
//			Convert string from user into computer intruction
//			using the muparser library
void Window::graphFunction() {
	double YVal;

	for (double XVal = XLowerLimit, index = 0.0; XVal < XUpperLimit; XVal += 0.001, index += 4) {
		// YVal = (XVal*XVal*XVal)-2*XVal;
		YVal = tan(XVal);
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