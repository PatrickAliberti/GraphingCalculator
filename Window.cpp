// To-Do
//			Figure out how to implement tick marks/Gridlines
//
//			Experiment with the axes?
#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Window.h"

using namespace std;

Window::Window(sf::RenderWindow& window) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	// Make default fullscreen?
	XLowerLimit = -20;
	XUpperLimit = 20;
	YLowerLimit = -20;
	YUpperLimit = 20;

	XAxis.setPrimitiveType(sf::Lines);
	XAxis.resize(2);
	YAxis.setPrimitiveType(sf::Lines);
	YAxis.resize(2);

	XTicks.setPrimitiveType(sf::Lines);
	double numOfTickPoints = ((XUpperLimit - XLowerLimit) / 1) * 2;
	XTicks.resize(numOfTickPoints);

	// Do the same for the Y-Axis

	function.setPrimitiveType(sf::Points);
	numOfPoints = (XUpperLimit - XLowerLimit) / 0.001;
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

	functionExpression = fx;

	function.setPrimitiveType(sf::Points);

	numOfPoints = (XUpperLimit - XLowerLimit) / 0.001;
	function.resize(numOfPoints);

	for (int index = 0; index < numOfPoints; index++) {
		function[index].color = sf::Color::Red;
	}
}

// TO-DO: 
//			Figure out how to convert string from user into computer intruction?
//			By using the muparser library
void Window::graphFunction() {
	double YVal;

	for (double XVal = XLowerLimit, index = 0.0; XVal < XUpperLimit; XVal += 0.001, index++) {
		YVal = sin(XVal);
		function[index].position = sf::Vector2f(XOrigin + XVal * 20, YOrigin - YVal * 20);
	}
}

void Window::graphAxes() {
	/*
	cout << "(" << XOrigin + XLowerLimit * 20 << ", " << YOrigin << ")" << endl;
	cout << "(" << XOrigin + XUpperLimit * 20 << ", " << YOrigin << ")" << endl;
	cout << "(" << YOrigin + YLowerLimit * 20 << ", " << XOrigin << ")" << endl;
	cout << "(" << YOrigin + YUpperLimit * 20 << ", " << XOrigin << ")" << endl;
	*/

	XAxis[0].position = sf::Vector2f(XOrigin + XLowerLimit * 20, YOrigin);
	XAxis[1].position = sf::Vector2f(XOrigin + XUpperLimit * 20, YOrigin);
	YAxis[0].position = sf::Vector2f(XOrigin, YOrigin + YLowerLimit * 20);
	YAxis[1].position = sf::Vector2f(XOrigin, YOrigin + YUpperLimit * 20);

	// XTicks[0].position = sf::Vector2f(XOrigin + XLowerLimit * 20, YOrigin + 5);
	// XTicks[1].position = sf::Vector2f(XOrigin + XLowerLimit * 20, YOrigin - 5);
	
	// Tick marks
	for (double i = XLowerLimit, j = 0, index = 0; i < XUpperLimit; i++, j++, index += 2) {
		double XCoord = (XOrigin + XLowerLimit + j) * 20;

		XTicks[index].position = sf::Vector2f(XCoord, YOrigin + 5);
		XTicks[index + 1].position = sf::Vector2f(XCoord, YOrigin - 5);
	}
}

void Window::drawTo(sf::RenderWindow& window) {
	window.draw(XAxis);
	window.draw(YAxis);
	window.draw(XTicks);
	
	window.draw(function);
}