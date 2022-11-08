#include <iostream>
#include <SFML/Graphics.hpp>

class button
{
public:
	button() {}

	button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor) {
		text.setString(t);
		text.setCharacterSize(charSize);

		buttonshape.setSize(size);
		buttonshape.setFillColor(bgColor);
	}

	void setFont(sf::Font &font) {
		text.setFont(font);
	}
	void setBackColor(sf::Color &color) {
		buttonshape.setFillColor(color);
	}


	void setposition(sf::Vector2f pos) {
		buttonshape.setPosition(pos);

		float posX = (pos.x + buttonshape.getLocalBounds().width/2)-(text.getLocalBounds().width/2);
		float posY = (pos.x + buttonshape.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
		text.setPosition({ posX, posY });
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(buttonshape);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = buttonshape.getPosition().x;
		float btnPosY = buttonshape.getPosition().y;

		float btnPosWidth = buttonshape.getPosition().x + buttonshape.getLocalBounds().width;
		float btnPosHeight = buttonshape.getPosition().y + buttonshape.getLocalBounds().height;


		if (mouseX<btnPosWidth && mouseX > btnPosX && mouseY < btnPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}


private:
	sf::RectangleShape buttonshape;
	sf::Text text;

};
