#ifndef ENGINE_H
#define ENGINE_H

#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include<SFML/Audio.hpp>
#include "apple.h"
#include "wall.h"
#include "snake.h"
#include<vector>
#include<deque>
#include<ctime>
#include<string>
#include<fstream>

using namespace std;
using namespace sf;




class Engine{

private:
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;
   // static const Time TimePerFrame ;

    vector<SnakeSection> snake;

    int SnakeDirection;
    deque<int> directionQueue;
    int speed;
    int sectionToAdd; //how many sections added to snake

    int appleEatenThisLevel;
    int appleEatenTotal;
    int score;

    Apple apple;

    vector<Wall> wallSection;
    int currentLevel;
    int maxLevel;
    vector <string> levels;
    
    Font mainFont;

    Text appleEatenText;
    Text currentLevelText;
    Text titleText;
    Text scoreText;
    Text winText;
    Text lostText;
    Text pressEnterText;
    Time timeSinceLastMove;
    Texture Game_Over;

    SoundBuffer bufferEatApple;
    Sound soundEatApple;
    
    SoundBuffer bufferNextLevel;
    SoundBuffer bufferCollision;
    Sound soundNextLevel;
    Sound soundCollision;

    

    int currentGameState;
    int lastGameState; // to start the game when pausing or gameover

public:
    enum Direction {UP, RIGHT, DOWN, LEFT};
    enum GameState {RUNNING, PAUSED, GAMEOVER, WINNING};
    Engine();
    
    
    void input();
        
    void addDirection (int newDirection);
        
    void update();  

    void draw();
       
    static void setupText(Text *textItem, const Font &font, const String &value, int size, Color colour);
        
    void newSnake();

    void addSnakeSection();

    void moveApple();
       
//check the level manifest file and make sure that we can open each level file
    void checkLevelFiles();
/*
    *Load a level from a file and check for "x" chacracters to add wall
    *levelNumber is the number of the level to load
*/
    void loadLevel(int levelNumber);

    //increase the level number, load the next level and reset the snake
    void beginNextLevel();

    void startThegame();

    void togglePause();

    void GameRun();
};


#endif