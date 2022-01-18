// To-Do
//			Have a menu screen where the user sets the upper and lower limits for the axes and the allows user to graph multiple different functions

#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Window.h"

// Constructors
Window::Window(sf::RenderWindow& window) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = -10;
	XUpperLimit = 10;
	YLowerLimit = -10;
	YUpperLimit = 10;

	XScale = 1;
	YScale = 1;

	setWindow();
}

Window::Window(sf::RenderWindow& window, double XLowerLim, double XUpperLim, double YLowerLim, double YUpperLim, double XScl, double YScl) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = XLowerLim;
	XUpperLimit = XUpperLim;
	YLowerLimit = YLowerLim;
	YUpperLimit = YUpperLim;

	XScale = XScl;
	YScale = YScl;

	setWindow();
}

/**
*	Private member function called by each constructor to set the vertex arrays once the origin and axis limit values are set
* 
*	No parameters, no return value
*/
void Window::setWindow() {
	// Background
	background.setPrimitiveType(sf::Quads);
	background.resize(4);
	background[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 25, YOrigin + 2 + YUpperLimit * 25);
	background[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 25, YOrigin + 2 + YUpperLimit * 25);
	background[2].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 25, YOrigin - 2 + YLowerLimit * 25);
	background[3].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 25, YOrigin - 2 + YLowerLimit * 25);
	for (int index = 0; index < 4; index++) {
		background[index].color = sf::Color{ 36, 36, 36 };
	}

	// X and Y-Axes
	XAxis.setPrimitiveType(sf::Lines);
	XAxis.resize(2);
	YAxis.setPrimitiveType(sf::Lines);
	YAxis.resize(2);
	XAxis[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * 25, YOrigin);
	XAxis[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * 25, YOrigin);
	YAxis[0].position = sf::Vector2f(XOrigin, YOrigin - 2 + YLowerLimit * 25);
	YAxis[1].position = sf::Vector2f(XOrigin, YOrigin + 2 + YUpperLimit * 25);
	for (int index = 0; index < 2; index++) {
		XAxis[index].color = sf::Color{ 105, 105, 105 };
		YAxis[index].color = sf::Color{ 105, 105, 105 };
	}

	// X-axis tick marks
	XTickMarks.setPrimitiveType(sf::Lines);
	int numOfXTickPoints = (XUpperLimit - XLowerLimit + 1) * 2;
	XTickMarks.resize(numOfXTickPoints);
	for (double XTickVal = XLowerLimit, index = 0.0; XTickVal < XUpperLimit + 1; XTickVal++, index += 2) {
		XTickMarks[index].position = sf::Vector2f(XOrigin + ((index / 2) * XScale) * 25 + XLowerLimit * 25, YOrigin + 5);
		XTickMarks[index + 1].position = sf::Vector2f(XOrigin + ((index / 2) * XScale) * 25 + XLowerLimit * 25, YOrigin - 5);

		if (((index / 2) * XScale) >= (XUpperLimit - XLowerLimit)) {
			break;
		}
	}

	for (int index = 0; index < numOfXTickPoints; index++) {
		XTickMarks[index].color = sf::Color{ 105, 105, 105 };
	}

	// Y-axis tick marks
	YTickMarks.setPrimitiveType(sf::Lines);
	int numOfYTickPoints = (YUpperLimit - YLowerLimit + 1) * 2;
	YTickMarks.resize(numOfYTickPoints);
	for (double YTickVal = YLowerLimit, index = 0.0; YTickVal < YUpperLimit + 1; YTickVal++, index += 2) {
		YTickMarks[index].position = sf::Vector2f(XOrigin - 5, YOrigin + ((index / 2) * YScale) * 25 + YLowerLimit * 25);
		YTickMarks[index + 1].position = sf::Vector2f(XOrigin + 5, YOrigin + ((index / 2) * YScale) * 25 + YLowerLimit * 25);

		if (((index / 2) * YScale) >= (XUpperLimit - YLowerLimit)) {
			break;
		}
	}

	for (int index = 0; index < numOfYTickPoints; index++) {
		YTickMarks[index].color = sf::Color{ 105, 105, 105 };
	}

	// Label Axes

	// Function plot
	function.setPrimitiveType(sf::Quads);
	int numOfFunctPoints = ((XUpperLimit - XLowerLimit) / .001) * 4;
	function.resize(numOfFunctPoints);
	for (int index = 0; index < numOfFunctPoints; index++) {
		function[index].color = sf::Color::Red;
	}
}

// Mutators
void Window::setXLowerLimit(double XLowLim) { XLowerLimit = XLowLim; }

void Window::setXUpperLimit(double XUppLim) { XUpperLimit = XUppLim; }

void Window::setYLowerLimit(double YLowLim) { YLowerLimit = YLowLim; }

void Window::setYUpperLimit(double XUppLim) { XUpperLimit = XUppLim; }

// Accessors
double Window::getXLowerLimit() { return XLowerLimit; }

double Window::getXUpperLimit() { return XUpperLimit; }

double Window::getYLowerLimit() { return YLowerLimit; }

double Window::getYUpperLimit() { return YUpperLimit; }

// To-Do: 
//			Convert string from user into computer intruction
//			using the muparser library
void Window::graphFunction(sf::RenderWindow& window) {
	double YVal;

	for (double XVal = XLowerLimit, index = 0.0; XVal < XUpperLimit; XVal += 0.001, index += 4) {
		// YVal = (XVal*XVal*XVal)-2*XVal;
		// YVal = tan(XVal);
		YVal = sin(XVal);
		if (YVal > YUpperLimit || YVal < YLowerLimit) {
			continue;
		}

		function[index].position = sf::Vector2f((XOrigin + XVal * 25) + 1.f, (YOrigin - YVal * 25) - 1.f);
		function[index + 1].position = sf::Vector2f((XOrigin + XVal * 25) - 1.f, (YOrigin - YVal * 25) - 1.f);
		function[index + 2].position = sf::Vector2f((XOrigin + XVal * 25) - 1.f, (YOrigin - YVal * 25) + 1.f);
		function[index + 3].position = sf::Vector2f((XOrigin + XVal * 25) + 1.f, (YOrigin - YVal * 25) + 1.f);
	}
}

void Window::drawTo(sf::RenderWindow& window) {
	window.draw(background);

	window.draw(XAxis);
	window.draw(YAxis);
	window.draw(XTickMarks);
	window.draw(YTickMarks);
	
	window.draw(function);
}