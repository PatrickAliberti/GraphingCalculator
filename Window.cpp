#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "Window.h"

using namespace std;

Window::Window(sf::RenderWindow& window) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	// Make default fullscreen?
	XLowerLimit = -10;
	XUpperLimit = 10;
	YLowerLimit = -10;
	YUpperLimit = 10;

	XAxis.setPrimitiveType(sf::Lines);
	XAxis.resize(2);
	YAxis.setPrimitiveType(sf::Lines);
	YAxis.resize(2);

	function.setPrimitiveType(sf::Points);

	numOfPoints = (XUpperLimit - XLowerLimit) / 0.01;
	function.resize(numOfPoints);

	functionExpression = "sin(X)";

	for (int index = 0; index < numOfPoints; index++) {
		function[index].color = sf::Color::Red;
	}
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

	numOfPoints = (XUpperLimit - XLowerLimit) / 0.01;
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

	for (double XVal = XLowerLimit, index = 0.0; XVal < XUpperLimit; XVal += 0.01, index++) {
		YVal = sin(XVal);
		function[index].position = sf::Vector2f(XOrigin + XVal * 20, YOrigin + YVal * 20);
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
}

void Window::drawTo(sf::RenderWindow& window) {
	window.draw(XAxis);
	window.draw(YAxis);
	
	window.draw(function);
}