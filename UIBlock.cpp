#include "UIBlock.h"

UIBlock::UIBlock(sf::Vertex topLeft, sf::Vertex topRight, sf::Vertex bottomRight, sf::Vertex bottomLeft) {
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


void UIBlock::drawTo(sf::RenderWindow & window) {
	window.draw(block);
}