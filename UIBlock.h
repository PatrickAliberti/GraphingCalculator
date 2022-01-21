#pragma once

#include <iostream>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "Window.h"

class UIBlock {
private:
	sf::VertexArray block;

	// Change all of these to vectors
	sf::CircleShape color[6];
	sf::Text label[12];
	sf::VertexArray box[12];

	sf::Text textbox[12];
	std::ostringstream text[12];
	bool isSelected[12];
	bool hasLimit;
	int limit;

	void inputLogic(Window&, int, int);

public:
	// Construtors
	UIBlock(sf::Vertex, sf::Vertex, sf::Vertex, sf::Vertex);
	UIBlock(sf::Vertex, sf::Vertex, sf::Vertex, sf::Vertex, int, bool, int);

	void deleteLastChar(int);

	void setBlock(sf::Vertex, sf::Vertex, sf::Vertex, sf::Vertex);
	void setColorCircles();
	void setFont(sf::Font&);
	void setLabels();
	void setBoxs();
	void setTextboxs();
	void setLimit(bool);
	void setLimit(bool, int);
	void setSelected(bool, int);

	// Use isMouseOver function for textbox selection

	void typedOn(Window&, sf::Event, int);
	std::string getTextbox(int index);

	void drawTo(sf::RenderWindow&);
};