#include "SFML/Graphics.hpp"

#include "shunting-yard.h"

#include "Window.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Graphing Calculator");

	Window graphWindow(window);
	graphWindow.graphFunction(window);

	std::map<std::string, double> vars;
	vars["pi"] = 3.14;
	calculator c1("pi-b");
	vars["b"] = 0.14;
	std::cout << c1.eval(&vars) << std::endl;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::MouseWheelMoved) {
				if (graphWindow.getZoom() <= 25) {
					graphWindow.setZoom(graphWindow.getZoom() + 1);
					continue;
				}
				else {
					graphWindow.setZoom(graphWindow.getZoom() + event.mouseWheel.delta);
					graphWindow.setWindow(window);
					graphWindow.graphFunction(window);

					window.clear();
					graphWindow.drawTo(window);
					window.display();
				}
			}
		}

		window.clear();
		graphWindow.drawTo(window);
		window.display();
	}

	return 0;
}