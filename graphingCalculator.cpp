#include <iostream>

#include "SFML/Graphics.hpp"

#include "shunting-yard.h"
#include "UIBlock.h"
#include "Window.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Graphing Calculator");

	Window graphWindow(window);
	UIBlock functInput(sf::Vector2f(20, 20), sf::Vector2f(350, 20), sf::Vector2f(350, 350), sf::Vector2f(20, 350), 15, true, 0);
	UIBlock buttons(sf::Vector2f(20, 700), sf::Vector2f(700, 700), sf::Vector2f(700, 980), sf::Vector2f(20, 980));

	sf::Font arial;
	arial.loadFromFile("fonts/arial.ttf");
	functInput.setFont(arial);
	functInput.setLimit(true, 18);

	graphWindow.graphFunction(window);

	int boxInputIndex = 0;

	while (window.isOpen()) {
		sf::Event event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			functInput.setSelected(true, 0);
			boxInputIndex = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			functInput.setSelected(true, 1);
			boxInputIndex = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			functInput.setSelected(true, 2);
			boxInputIndex = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			functInput.setSelected(true, 3);
			boxInputIndex = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			functInput.setSelected(true, 4);
			boxInputIndex = 4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			functInput.setSelected(true, 5);
			boxInputIndex = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			for (int index = 0; index < 12; index++) {
				functInput.setSelected(false, index);
			}
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::TextEntered) {
				functInput.typedOn(graphWindow, event, boxInputIndex);
			}

			// Zoom
			else if (event.type == sf::Event::MouseWheelMoved) {
				if (graphWindow.getZoom() <= 5) {
					graphWindow.setZoom(graphWindow.getZoom() + 1);
					graphWindow.setZoom(graphWindow.getZoom() + (event.mouseWheel.delta * 4));
					graphWindow.setWindow(window);
					graphWindow.graphFunction(window);

					window.clear();
					graphWindow.drawTo(window);
					functInput.drawTo(window);
					buttons.drawTo(window);
					window.display();
					continue;
				}

				graphWindow.setZoom(graphWindow.getZoom() + (event.mouseWheel.delta * 4));
				graphWindow.setWindow(window);
				graphWindow.graphFunction(window);

				window.clear();
				graphWindow.drawTo(window);
				functInput.drawTo(window);
				buttons.drawTo(window);
				window.display();
			}
		}

		window.clear();
		graphWindow.drawTo(window);
		functInput.drawTo(window);
		buttons.drawTo(window);
		window.display();
	}

	return 0;
}