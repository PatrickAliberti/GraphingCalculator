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