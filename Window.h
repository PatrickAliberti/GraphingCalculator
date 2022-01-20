#pragma once

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

	double Zoom = 50;

	sf::VertexArray background;
	sf::VertexArray XAxis;
	sf::VertexArray YAxis;
	sf::VertexArray XTickMarks;
	sf::VertexArray YTickMarks;

	sf::VertexArray function;

	std::string functionExpression;

public:
	// Constructors
	Window(sf::RenderWindow&);
	Window(sf::RenderWindow&, double, double, double, double, double, double, std::string);

	// Mutators
	void setXOrigin(double);
	void setYOrigin(double);
	void setXLowerLimit(double);
	void setXUpperLimit(double);
	void setYLowerLimit(double);
	void setYUpperLimit(double);
	void setXScale(double);
	void setYScale(double);
	void setZoom(double);
	void setFunctExpr(std::string);

	// Accessors
	double getXOrigin();
	double getYOrigin();
	double getXLowerLimit();
	double getXUpperLimit();
	double getYLowerLimit();
	double getYUpperLimit();
	double getXScale();
	double getYScale();
	double getZoom();
	std::string getFunctExpr();

	void setWindow(sf::RenderWindow&);
	void graphFunction(sf::RenderWindow&);
	void drawTo(sf::RenderWindow&);
};