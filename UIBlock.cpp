#include "UIBlock.h"

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

UIBlock::UIBlock(sf::Vertex topLeft, sf::Vertex topRight, sf::Vertex bottomRight, sf::Vertex bottomLeft) {
	setBlock(topLeft, topRight, bottomRight, bottomLeft);
}

// Constructor used for UIBlock with textboxs
UIBlock::UIBlock(sf::Vertex topLeft, sf::Vertex topRight, sf::Vertex bottomRight, sf::Vertex bottomLeft, int size, bool sel, int index) {
	setBlock(topLeft, topRight, bottomRight, bottomLeft);
	setColorCircles();
	setLabels();
	setBoxs();
	setTextboxs();

	textbox[index].setCharacterSize(size);

	for (int i = 0; i < 12; i++) {
		isSelected[i] = false;
	}

	isSelected[index] = sel;

	if (sel)
		textbox[index].setString("_");
	else
		textbox[index].setString("");
}

// Constructor used for UIBlock with buttons

void UIBlock::inputLogic(Window& graphWin, int charTyped, int index) {
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
		text[index] << static_cast<char>(charTyped);
	else if (charTyped == DELETE_KEY) {
		if (text[index].str().length() > 0) {
			deleteLastChar(index);
		}
	}
	textbox[index].setString(text[index].str() + "_");

	graphWin.setFunctExpr(charTyped);
}

void UIBlock::deleteLastChar(int index) {
	std::string t = text[index].str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}

	text[index].str("");
	text[index] << newT;

	textbox[index].setString(text[index].str());
}

void UIBlock::setBlock(sf::Vertex topLeft, sf::Vertex topRight, sf::Vertex bottomRight, sf::Vertex bottomLeft) {
	// Set background block
	block.setPrimitiveType(sf::Quads);
	block.resize(4);
	block[0].position = topLeft.position;
	block[1].position = topRight.position;
	block[2].position = bottomRight.position;
	block[3].position = bottomLeft.position;
	for (int index = 0; index < 4; index++) {
		block[index].color = sf::Color{ 25, 25, 25 };
	}
}

void UIBlock::setColorCircles() {
	for (int index = 0; index < 6; index++) {
		color[index].setRadius(7);
		color[index].setPointCount(10);

		color[index].setPosition(sf::Vector2f(block[0].position.x + 20, block[0].position.x + ((index + 1) * 25)));
	}

	color[0].setFillColor(sf::Color::Red);
	color[1].setFillColor(sf::Color::Blue);
	color[2].setFillColor(sf::Color::Green);
	color[3].setFillColor(sf::Color::White);
	color[4].setFillColor(sf::Color::Yellow);
	color[5].setFillColor(sf::Color::Cyan);
}

void UIBlock::setFont(sf::Font& font) {
	for (int index = 0; index < 12; index++) {
		label[index].setFont(font);
		textbox[index].setFont(font);
	}
}

void UIBlock::setLabels() {
	for (int index = 0; index < 12; index++) {
		label[index].setString("Y = ");
		label[index].setPosition(sf::Vector2f(block[0].position.x + 50, block[0].position.y + ((index + 1) * 25)));
		label[index].setCharacterSize(15);
	}
}

void UIBlock::setBoxs() {
	for (int index = 0; index < 12; index++) {
		box[index].setPrimitiveType(sf::Quads);
		box[index].resize(4);

		box[index][0].position = sf::Vector2f(sf::Vector2f(block[0].position.x + 75, block[0].position.y + 9 + ((index + 1) * 27)));
		box[index][1].position = sf::Vector2f(sf::Vector2f(block[0].position.x + 75, block[0].position.y - 9 + ((index + 1) * 27)));
		box[index][2].position = sf::Vector2f(sf::Vector2f(block[0].position.x + 300, block[0].position.y - 9 + ((index + 1) * 27)));
		box[index][3].position = sf::Vector2f(sf::Vector2f(block[0].position.x + 300, block[0].position.y + 9 + ((index + 1) * 27)));
		
		box[index][0].color = sf::Color{ 90, 90, 90 };
		box[index][1].color = sf::Color{ 90, 90, 90 };
		box[index][2].color = sf::Color{ 90, 90, 90 };
		box[index][3].color = sf::Color{ 90, 90, 90 };
	}
}

void UIBlock::setTextboxs() {
	for (int index = 0; index < 12; index++) {
		textbox[index].setPosition(sf::Vector2f(block[0].position.x + 80, block[0].position.y - 10 + ((index + 1) * 27)));
		textbox[index].setCharacterSize(15);
		textbox[index].setFillColor(sf::Color::Black);
	}
}

void UIBlock::setLimit(bool ToF) {
	hasLimit = ToF;
}

void UIBlock::setLimit(bool ToF, int lim) {
	hasLimit = ToF;
	limit = lim;
}

void UIBlock::setSelected(bool sel, int index) {
	isSelected[index] = sel;
	if (!sel) {
		std::string t = text[index].str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++) {
			newT += t[i];
		}

		textbox[index].setString(newT);
	}
}

void UIBlock::typedOn(Window& graphWin, sf::Event input, int index) {
	int charTyped;

	std::cout << isSelected[index] << std::endl;

	if (isSelected[index]) {
		charTyped = input.text.unicode;
		if (charTyped < 128) {
			if (hasLimit) {
				if (text[index].str().length() <= limit) {
					inputLogic(graphWin, charTyped, index);
				}
				else if (text[index].str().length() > limit && charTyped == DELETE_KEY)
					deleteLastChar(index);
			}
			else {
				inputLogic(graphWin, charTyped, index);
			}
		}
	}
}

std::string UIBlock::getTextbox(int index) {
	//
}


void UIBlock::drawTo(sf::RenderWindow & window) {
	window.draw(block);
	
	for (int index = 0; index < 6; index++) {
		window.draw(color[index]);
		window.draw(label[index]);
		window.draw(box[index]);
		window.draw(textbox[index]);
	}
}