#ifndef APPLE_H
#define APPLE_H

#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RectangleShape.hpp>

using namespace sf;


class Apple {
 private:
    RectangleShape sprite;

public:
    Apple();

    void setPosition(Vector2f newPosition);

    RectangleShape getSprite();
};

#endif