#include "stickman.hpp"

Stickman::Stickman() {
	Vector2f startingPosition(400, 300);
	//sprite.setScale(0.0390625f, 0.0390625f);
	sprite.setSize(Vector2f(20, 20));
	//sprite.setFillColor(Color::Red);
	stickmanTexture.loadFromFile("assets/textures/stickman.png");
	sprite.setTexture(&stickmanTexture);
	sprite.setPosition(startingPosition);
}

void Stickman::setPosition(Vector2f newPosition) {
	sprite.setPosition(newPosition);
}

RectangleShape Stickman::getSprite() {
	return sprite;
}