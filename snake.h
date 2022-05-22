#ifndef SNAKE_H
#define SNAKE_H

#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class SnakeSection{

private:
    Vector2f position;
    RectangleShape section;

public:
    SnakeSection(Vector2f startPosition );
        
    
    //SnakeSection(){};
    Vector2f getPosition();
    

    void setPosition(Vector2f newPosition);
        
    RectangleShape getShape();
      
    void update();
};


#endif