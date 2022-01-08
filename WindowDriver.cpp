#include "SFML/Graphics.hpp"

#include "Window.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Test");

	Window graphWindow(window);
	graphWindow.graph();

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