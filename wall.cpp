#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Graphics/RectangleShape.hpp>
#include"wall.h"

using namespace sf;

Wall::Wall(Vector2f position, Vector2f size){
    wallshape.setSize(size);
    wallshape.setFillColor(Color::Blue);
    wallshape.setPosition(position);
}

RectangleShape Wall::getShape(){
    return wallshape;
}