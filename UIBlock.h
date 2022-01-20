#pragma once

#include "SFML/Graphics.hpp"

class UIBlock {
private:
	sf::VertexArray block;

public:
	// Construtors
	UIBlock(sf::Vertex, sf::Vertex, sf::Vertex, sf::Vertex);

	void drawTo(sf::RenderWindow&);
};