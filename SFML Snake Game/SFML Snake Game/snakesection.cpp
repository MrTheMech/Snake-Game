#include "snakesection.hpp"

SnakeSection::SnakeSection(Vector2f startPosition) {
	section.setSize(Vector2f(20, 20));
	//section.setFillColor(Color::Red);
	snakeTexture.loadFromFile("assets/textures/snake.png");
	section.setTexture(&snakeTexture);
	section.setTextureRect(sf::IntRect(100, 100, 100, 100));
	section.setPosition(startPosition);
	position = startPosition;
}

Vector2f SnakeSection::getPosition() {
	return position;
}

void SnakeSection::setPosition(Vector2f newPosition) {
	section.setTexture(&snakeTexture);
	section.setTextureRect(IntRect(10, 10, 100, 100));
	position = newPosition;
}

RectangleShape SnakeSection::getShape() {
	return section;
}

void SnakeSection::update() {
	section.setTexture(&snakeTexture);
	section.setPosition(position);

}