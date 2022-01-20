// To-Do
//			Have a menu screen where the user sets the upper and lower limits for the axes and the allows user to graph multiple different functions

#include <cmath>
#include <iostream>

#include "SFML/Graphics.hpp"

#include "shunting-yard.h"
#include "Window.h"

// Constructors
Window::Window(sf::RenderWindow& window) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;
	// XOrigin = 200;
	// YOrigin = 200;

	XLowerLimit = -200;
	XUpperLimit = 200;
	YLowerLimit = -200;
	YUpperLimit = 200;

	XScale = 1;
	YScale = 1;

	setWindow(window);

	functionExpression = "-tan(x)";
}

Window::Window(sf::RenderWindow& window, double XLowerLim, double XUpperLim, double YLowerLim, double YUpperLim, double XScl, double YScl, std::string fxEx) {
	XOrigin = window.getSize().x / 2;
	YOrigin = window.getSize().y / 2;

	XLowerLimit = XLowerLim;
	XUpperLimit = XUpperLim;
	YLowerLimit = YLowerLim;
	YUpperLimit = YUpperLim;

	XScale = XScl;
	YScale = YScl;

	setWindow(window);

	functionExpression = fxEx;
}

/**
*	Private member function called by each constructor to set the vertex arrays once the origin and axis limit values are set
* 
*	No parameters, no return value
*/
void Window::setWindow(sf::RenderWindow& window) {
	// Background
	background.setPrimitiveType(sf::Quads);
	background.resize(4);
	background[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * Zoom, YOrigin + 2 + YUpperLimit * Zoom);
	background[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * Zoom, YOrigin + 2 + YUpperLimit * Zoom);
	background[2].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * Zoom, YOrigin - 2 + YLowerLimit * Zoom);
	background[3].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * Zoom, YOrigin - 2 + YLowerLimit * Zoom);
	for (int index = 0; index < 4; index++) {
		background[index].color = sf::Color{ 36, 36, 36 };
	}

	// X and Y-Axes
	XAxis.setPrimitiveType(sf::Lines);
	XAxis.resize(2);
	YAxis.setPrimitiveType(sf::Lines);
	YAxis.resize(2);
	XAxis[0].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * Zoom, YOrigin);
	XAxis[1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * Zoom, YOrigin);
	YAxis[0].position = sf::Vector2f(XOrigin, YOrigin - 2 + YLowerLimit * Zoom);
	YAxis[1].position = sf::Vector2f(XOrigin, YOrigin + 2 + YUpperLimit * Zoom);
	for (int index = 0; index < 2; index++) {
		XAxis[index].color = sf::Color{ 145, 145, 145 };
		YAxis[index].color = sf::Color{ 145, 145, 145 };
	}

	// X-axis tick marks
	XTickMarks.setPrimitiveType(sf::Lines);
	int numOfXTickPoints = (XUpperLimit - XLowerLimit + 1) * 2;
	XTickMarks.resize(numOfXTickPoints);
	for (double XTickVal = XLowerLimit, index = 0.0; XTickVal < XUpperLimit + 1; XTickVal++, index += 2) {
		XTickMarks[index].position = sf::Vector2f(XOrigin + ((index / 2) * XScale) * Zoom + XLowerLimit * Zoom, YOrigin - 2 + YLowerLimit * Zoom);
		XTickMarks[index + 1].position = sf::Vector2f(XOrigin + ((index / 2) * XScale) * Zoom + XLowerLimit * Zoom, YOrigin + 2 + YUpperLimit * Zoom);
	}

	for (int index = 0; index < numOfXTickPoints; index++) {
		XTickMarks[index].color = sf::Color{ 60, 60, 60 };
	}

	// Y-axis tick marks
	YTickMarks.setPrimitiveType(sf::Lines);
	int numOfYTickPoints = (YUpperLimit - YLowerLimit + 1) * 2;
	YTickMarks.resize(numOfYTickPoints);
	for (double YTickVal = YLowerLimit, index = 0.0; YTickVal < YUpperLimit + 1; YTickVal++, index += 2) {
		YTickMarks[index].position = sf::Vector2f(XOrigin - 2 + XLowerLimit * Zoom, YOrigin + ((index / 2) * YScale) * Zoom + YLowerLimit * Zoom);
		YTickMarks[index + 1].position = sf::Vector2f(XOrigin + 2 + XUpperLimit * Zoom, YOrigin + ((index / 2) * YScale) * Zoom + YLowerLimit * Zoom);

		if (((index / 2) * YScale) >= (XUpperLimit - YLowerLimit)) {
			break;
		}
	}

	for (int index = 0; index < numOfYTickPoints; index++) {
		YTickMarks[index].color = sf::Color{ 60, 60, 60 };
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
void Window::setXOrigin(double XOrig) { XOrigin = XOrig; }
void Window::setYOrigin(double YOrig) { YOrigin = YOrig; }
void Window::setXLowerLimit(double XLowLim) { XLowerLimit = XLowLim; }
void Window::setXUpperLimit(double XUppLim) { XUpperLimit = XUppLim; }
void Window::setYLowerLimit(double YLowLim) { YLowerLimit = YLowLim; }
void Window::setYUpperLimit(double XUppLim) { XUpperLimit = XUppLim; }
void Window::setXScale(double XScl) { XScale = XScl; }
void Window::setYScale(double YScl) { YScale = YScl; }
void Window::setZoom(double Z) { Zoom = Z; }
void Window::setFunctExpr(std::string functExpr) { functionExpression = functExpr; }

// Accessors
double Window::getXOrigin() { return XOrigin; }
double Window::getYOrigin() { return YOrigin; }
double Window::getXLowerLimit() { return XLowerLimit; }
double Window::getXUpperLimit() { return XUpperLimit; }
double Window::getYLowerLimit() { return YLowerLimit; }
double Window::getYUpperLimit() { return YUpperLimit; }
double Window::getXScale() { return XScale; }
double Window::getYScale() { return YScale; }
double Window::getZoom() { return Zoom; }
std::string Window::getFunctExpr() { return functionExpression; }

// To-Do: 
//			Convert string from user into computer intruction
//			using shunting-yard header
void Window::graphFunction(sf::RenderWindow& window) {
	const char* functionExpressionArg = functionExpression.c_str();
	std::map<std::string, double> vars;
	std::map<std::string, double> vars2;
	calculator fx(functionExpressionArg);

	double YVal, YVal2;
	for (double XVal = XLowerLimit, index = 0.0; XVal < XUpperLimit; XVal += 0.001, index += 4) {
		vars["X"] = XVal;
		vars2["X"] = XVal + 1;
		YVal = fx.eval(&vars);
		YVal2 = fx.eval(&vars2);

		if (YVal > YUpperLimit || YVal < YLowerLimit) {
			continue;
		}

		/*
		if ((YVal2 - YVal) * 100000000 < 2.5 || (YVal - YVal2) * 100000000 > 2.5) {
			function[index].position = sf::Vector2f((XOrigin + XVal * Zoom) + 1.f, (YOrigin - YVal * Zoom) - YVal / 4);
			function[index + 1].position = sf::Vector2f((XOrigin + XVal * Zoom) - 1.f, (YOrigin - YVal * Zoom) - YVal / 4);
			function[index + 2].position = sf::Vector2f((XOrigin + XVal * Zoom) - 1.f, (YOrigin - YVal * Zoom) + YVal / 4);
			function[index + 3].position = sf::Vector2f((XOrigin + XVal * Zoom) + 1.f, (YOrigin - YVal * Zoom) + YVal / 4);
		}
		*/
		else {
			function[index].position = sf::Vector2f((XOrigin + XVal * Zoom) + 1.f, (YOrigin - YVal * Zoom) - 1.f);
			function[index + 1].position = sf::Vector2f((XOrigin + XVal * Zoom) - 1.f, (YOrigin - YVal * Zoom) - 1.f);
			function[index + 2].position = sf::Vector2f((XOrigin + XVal * Zoom) - 1.f, (YOrigin - YVal * Zoom) + 1.f);
			function[index + 3].position = sf::Vector2f((XOrigin + XVal * Zoom) + 1.f, (YOrigin - YVal * Zoom) + 1.f);
		}
	}
}

void Window::drawTo(sf::RenderWindow& window) {
	window.draw(background);

	window.draw(XTickMarks);
	window.draw(YTickMarks);
	window.draw(XAxis);
	window.draw(YAxis);

	window.draw(function);
}