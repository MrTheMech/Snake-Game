#ifndef NIBBLES_02_STICKMAN_HPP
#define NIBBLES_02_STICKMAN_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Stickman {
private:
    RectangleShape sprite;

public:
	Texture stickmanTexture;
    Stickman();

    void setPosition(Vector2f newPosition);
    RectangleShape getSprite();
};


#endif //NIBBLES_02_STCIKMAN_HPP