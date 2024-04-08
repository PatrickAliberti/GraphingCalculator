/*
#include <iostream>

#include "SFML/Graphics.hpp"

#include "shunting-yard.h"
#include "UIBlock.h"
#include "Window.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Graphing Calculator");

	Window graphWindow(window);
	UIBlock functInput(sf::Vector2f(670, 700), sf::Vector2f(950, 700), sf::Vector2f(950, 950), sf::Vector2f(670, 950));

	// Get function expression from user
	std::string equation;
	std::cout << "Enter an equation: ";
	std::cin >> equation;
	graphWindow.setFunctExpr(equation);
	graphWindow.graphFunction(window);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			
			// Zoom
			if (event.type == sf::Event::MouseWheelMoved) {
				if (graphWindow.getZoom() <= 5) {
					graphWindow.setZoom(graphWindow.getZoom() + 1);
					graphWindow.setZoom(graphWindow.getZoom() + (event.mouseWheel.delta * 4));
					graphWindow.setWindow(window);
					graphWindow.graphFunction(window);

					window.clear();
					graphWindow.drawTo(window);
					functInput.drawTo(window);
					window.display();
					continue;
				}

				graphWindow.setZoom(graphWindow.getZoom() + (event.mouseWheel.delta * 4));
				graphWindow.setWindow(window);
				graphWindow.graphFunction(window);

				window.clear();
				graphWindow.drawTo(window);
				functInput.drawTo(window);
				window.display();
			}
		}

		window.clear();
		graphWindow.drawTo(window);
		functInput.drawTo(window);
		window.display();
	}

	return 0;
}
*/
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "shuntingYard.hpp"

// Function to evaluate the parsed equation
double evaluateEquation(const std::string &equation, double x) {
    Calculator calculator(equation);
    return calculator.calculateY(x);
}

// Function to draw the graph of the equation
void drawGraph(sf::RenderWindow &window, const std::string &equation, double xMin, double xMax, double step) {
    sf::VertexArray graph(sf::LineStrip);
    graph.setPrimitiveType(sf::LineStrip);

    // Evaluate and draw points
    for (double x = xMin; x <= xMax; x += step) {
        double y = evaluateEquation(equation, x);
        graph.append(sf::Vertex(sf::Vector2f(x, -y), sf::Color::Blue)); // Note the negative sign for y (SFML's y-axis is inverted)
    }

    // Draw x-axis
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(xMin, 0);
    xAxis[1].position = sf::Vector2f(xMax, 0);
    xAxis[0].color = sf::Color::Black;
    xAxis[1].color = sf::Color::Black;
    window.draw(xAxis);

    // Draw y-axis
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(0, -window.getSize().y / 2);
    yAxis[1].position = sf::Vector2f(0, window.getSize().y / 2);
    yAxis[0].color = sf::Color::Black;
    yAxis[1].color = sf::Color::Black;
    window.draw(yAxis);

    // Draw grid lines and labels
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text label;
    label.setFont(font);
    label.setCharacterSize(12);
    label.setFillColor(sf::Color::Black);

    double range = xMax - xMin;
    int numLines = static_cast<int>(range / step);

    for (int i = 1; i <= numLines; ++i) {
        // Draw grid lines
        double xPos = xMin + i * step;
        sf::VertexArray gridLine(sf::Lines, 2);
        gridLine[0].position = sf::Vector2f(xPos, -window.getSize().y / 2);
        gridLine[1].position = sf::Vector2f(xPos, window.getSize().y / 2);
        gridLine[0].color = sf::Color(200, 200, 200); // Light gray color
        gridLine[1].color = sf::Color(200, 200, 200);
        window.draw(gridLine);

        // Draw x-axis labels
        label.setString(std::to_string(static_cast<int>(xPos)));
        label.setPosition(xPos - 10, 10); // Adjust label position for better alignment
        window.draw(label);
    }

    // Draw y-axis labels
    for (double y = -window.getSize().y / 2; y <= window.getSize().y / 2; y += 50) {
        if (y != 0) {
            label.setString(std::to_string(static_cast<int>(-y)));
            label.setPosition(10, y - 10); // Adjust label position for better alignment
            window.draw(label);
        }
    }

    window.draw(graph);
}

int main() {
    // Set up window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Function Graph");

    std::string equation;
    double xMin, xMax, step;

    // Get equation and range from user
    std::cout << "Enter the function equation (use 'x' as the variable): ";
    std::getline(std::cin, equation);

    std::cout << "Enter the minimum value of x: ";
    std::cin >> xMin;

    std::cout << "Enter the maximum value of x: ";
    std::cin >> xMax;

    std::cout << "Enter the step size: ";
    std::cin >> step;

    // Event loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw the graph
        drawGraph(window, equation, xMin, xMax, step);

        window.display();
    }

    return 0;
}
