#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include "apple.h"


using namespace std;
using namespace sf;

Apple::Apple(){
    Vector2f startingPosition(400, 300);
    sprite.setSize(Vector2f(20, 20));
    sprite.setFillColor(Color::Red);
    sprite.setPosition(startingPosition);        
}

void Apple::setPosition(Vector2f newPosition){
    sprite.setPosition(newPosition);//setPosition nay la ham cua sfml
}

RectangleShape Apple::getSprite(){
    return sprite;
}