#include "SFML/Graphics.hpp"

#include "Window.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Graphing Calculator");

	Window graphWindow(window);
	graphWindow.graphFunction();

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		graphWindow.drawTo(window);
		window.display();
	}

	return 0;
}