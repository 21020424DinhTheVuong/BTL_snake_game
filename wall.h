#ifndef WALL_H
#define WALL_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class Wall{
private:
    RectangleShape wallshape;

public:
    Wall(Vector2f position, Vector2f size);
        
    RectangleShape getShape();
        
};

#endif