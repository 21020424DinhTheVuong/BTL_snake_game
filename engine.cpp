#include "engine.h"
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



Engine::Engine(){
    resolution = Vector2f(1200, 800);
    window.create (VideoMode(resolution.x, resolution.y), "SDL Game!" );
    window.setFramerateLimit(FPS);
    maxLevel = 0;
    checkLevelFiles();

    startThegame();
    mainFont.loadFromFile("PixellettersFull.ttf");

    
    setupText(&titleText, mainFont, "Player", 28, Color::Yellow);
    FloatRect titleTextBounds = titleText.getLocalBounds();
    
    titleText.setPosition(Vector2f(resolution.x/2 - titleTextBounds.width/2, -9));

    setupText(&currentLevelText, mainFont, "level 1", 28, Color::Yellow);
    currentLevelText.setPosition(Vector2f(15, -9));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();

    // setupText(&appleEatenText, mainFont, "apple 0", 28, Color::Yellow);
    // appleEatenText.setPosition(
    //             Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));

    setupText(&scoreText, mainFont, "Score: " + to_string(score), 28, Color::Yellow);
    FloatRect scoreTextBounds = scoreText.getGlobalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

    setupText(&winText, mainFont, "WINNING", 120, Color::Yellow);
    FloatRect winTextBounds = winText.getGlobalBounds();
    winText.setPosition(Vector2f(resolution.x/2 - winTextBounds.width/2, 300));
    winText.setOutlineColor(Color::Black);
    winText.setOutlineThickness(2);

    setupText(&pressEnterText, mainFont, "Press Enter to play again", 70,Color::Yellow);
    FloatRect pressEnterTextBounds = pressEnterText.getGlobalBounds();
    pressEnterText.setPosition(Vector2f(resolution.x/2 - pressEnterTextBounds.width/2, 400));
    pressEnterText.setOutlineColor(Color::Red);
    pressEnterText.setOutlineThickness(2);


    setupText(&lostText, mainFont, "LOST! You are so bad", 120, Color::Yellow);
    FloatRect lostTextBounds = lostText.getGlobalBounds();
    lostText.setPosition(Vector2f(resolution.x/2 - lostTextBounds.width/2, 300));
    lostText.setOutlineColor(Color::Black);//set mau cho duong vien
    lostText.setOutlineThickness(2);//set duong vien cho van ban

    bufferEatApple.loadFromFile("destroy.wav");
    soundEatApple.setBuffer(bufferEatApple);
    
    bufferNextLevel.loadFromFile("level.wav");
    soundNextLevel.setBuffer(bufferNextLevel);

    bufferCollision.loadFromFile("no.wav");
    soundCollision.setBuffer(bufferCollision);

   
}



void Engine::input(){
    Event event;

        while(window.pollEvent(event)){
            switch (event.type ){
                case Event::Closed:
                    window.close();
                    break;
                case Event::EventType::KeyPressed:
                    //quit game
                    if(Keyboard::Escape == event.key.code){
                        window.close();
                    }

                    //pause game
                    if(Keyboard::P == event.key.code){
                        
                        togglePause();
                        
                    }
                    
                    //start new game
                    if(currentGameState == GameState::GAMEOVER || currentGameState == GameState::PAUSED){ //PAUSED thay cho WINNING
                        //togglePause();
                        if(Keyboard::Enter == event.key.code ){
                            
                            startThegame();
                        }
                    } 

                    //direction
                    if(event.key.code == Keyboard::Up){
                        addDirection(Direction::UP);
                    }
                    else if(event.key.code == Keyboard::Down){
                        addDirection(Direction::DOWN);
                    }
                    else if(event.key.code == Keyboard::Left){
                        addDirection(Direction::LEFT);
                    }
                    else if(event.key.code == Keyboard::Right){
                        addDirection(Direction::RIGHT);
                    } 
                    break;
                
            }
        }
}

void Engine::startThegame(){
    score = 0;
    speed = 10;
    SnakeDirection = Direction::RIGHT;

    timeSinceLastMove = Time::Zero;

    sectionToAdd = 0;
    directionQueue.clear();
    wallSection.clear();//clear wall before begin next level game
    appleEatenThisLevel = 0;
    appleEatenTotal = 0;
    currentLevel = 1;
    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentGameState = GameState::RUNNING;
    lastGameState = currentGameState;

    currentLevelText.setString("level " + to_string(currentLevel));
    appleEatenText.setString("apple " + to_string(appleEatenTotal));

    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    appleEatenText.setPosition(
                Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
    scoreText.setString("Score: " + to_string(score));

    FloatRect scoreTextBounds = scoreText.getGlobalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15, -9));
}

void Engine::addDirection(int newDirection){
    if(directionQueue.empty()){
            directionQueue.emplace_back(newDirection);
        }
    else {
        if(directionQueue.back() != newDirection){
            directionQueue.emplace_back(newDirection);    
        }
    }
}

void Engine::update(){
    //update snake position
        if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()){
            Vector2f thisSectionPosition = snake[0].getPosition();
            Vector2f lastSectionPosition = thisSectionPosition;

            if(directionQueue.empty() == false){
                //make sure we dont reverse direction
                switch (SnakeDirection) {
                    case Direction::UP:
                        if(directionQueue.front() != Direction::DOWN){
                            SnakeDirection = directionQueue.front();
                        }
                        break;
                    case Direction::DOWN:
                        if(directionQueue.front() != Direction::UP){
                            SnakeDirection = directionQueue.front();
                        }
                        break;
                    case Direction::LEFT:
                        if(directionQueue.front() != Direction::RIGHT){
                            SnakeDirection = directionQueue.front();
                        }
                        break;
                    case Direction::RIGHT:
                        if(directionQueue.front() != Direction::LEFT){
                            SnakeDirection = directionQueue.front();
                        }
                        break;
            }

            directionQueue.pop_front();
        }
        
       

        // FloatRect scoreTextBounds = scoreText.getGlobalBounds();
        // scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width -15 , -9));

        //grow the snake
        if(sectionToAdd){
            addSnakeSection();
            sectionToAdd--;
        }

        //update snake's head position
        switch (SnakeDirection) {
            case Direction::RIGHT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
                break;
            case Direction::DOWN:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
                break;
            case Direction::LEFT:
                snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
                break;
            case Direction::UP:
                snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
                break;  
            //cac ham setPosition nay la ham thanh vien cua class snake  
        }

        //update snake's tail position
        for(int s=1 ; s < snake.size(); s++){
            thisSectionPosition = snake[s].getPosition();//getPosition la ham thanh vien cua class snake
            snake[s].setPosition(lastSectionPosition);//setPosition la ham thanh vien cua class snake
            lastSectionPosition = thisSectionPosition;
        }
        //run snake section update function
        for(auto & s : snake){
            s.update();//update nay la ham thanh vien cua class snakeSection
        }

        //collision detection with apple
        if(snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())){
            score += 1;
            appleEatenThisLevel += 1;
            appleEatenTotal += 1;
            
            soundEatApple.play();
            // appleEatenText.setString("apple " + to_string(appleEatenTotal));
            FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
            
            appleEatenText.setPosition(
                    Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
            
            scoreText.setString("Score: " + to_string(score));

            bool beginningNextLevel = false;
            if(appleEatenThisLevel >= 10){
                if(currentLevel < maxLevel){
                    beginningNextLevel = true;
                    beginNextLevel();
                    soundNextLevel.play();
                }
            }
            if(!beginningNextLevel){
                sectionToAdd += 4;
                speed++;
                moveApple();
            }
        }

        //Collision detection
        for(int s=1;s<snake.size();s++){
            if(snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())){
                currentGameState = GameState::GAMEOVER;
                
                window.draw(pressEnterText);
                soundCollision.play();
            }
        }

        //collision detection wall

        for(auto & w : wallSection){
            if(snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())){
                currentGameState = GameState::GAMEOVER;
                window.draw(pressEnterText);
                soundCollision.play();
            }
        }
        //go through wall


        //winning game
        if(appleEatenTotal ==  maxLevel * 10){
            currentGameState = GameState::WINNING;
            soundNextLevel.play();
        }
        timeSinceLastMove = Time::Zero; //dat thoi gian ve lai 0, neu ko thi con ran se chay qua ban do
    }
}// end update snake direction

void Engine::GameRun(){
    Clock clock;

    //main loop, run until the window is closed;
    while (window.isOpen()){
        Time dt = clock.restart();
        

        if(currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER){
            //if pausing, then check input, if un-pause, continue game loop
            input();

            //draw the gameover screen
            if(currentGameState == GameState::GAMEOVER){
                draw();
            }

             //sleep(milliseconds(2));
             continue;
        }
        timeSinceLastMove += dt;
        input();    
        update();
        draw();
    }
    window.clear();
    window.display();
}

void Engine::draw(){
     window.clear(Color::Black);

    //draw wall
    for(auto & w : wallSection){
        window.draw(w.getShape());
    }
    //draw apple
    window.draw( apple.getSprite());
    //draw snake section;
    for(auto & s : snake){
        window.draw(s.getShape());
    }

    //draw text
    window.draw(titleText);
    window.draw(currentLevelText);
    window.draw(appleEatenText);
    window.draw(scoreText);

    if(currentGameState == GameState::WINNING){
        togglePause();
        window.draw(winText);
        window.draw(pressEnterText);
    }
    
    if(currentGameState == GameState::GAMEOVER){
        togglePause();
        window.draw(lostText);
        window.draw(pressEnterText);
    }
    //  if(currentGameState == GameState::GAMEOVER){
    //     Game_Over.loadFromFile("image/gameOver1.jpg");
    //     Sprite GameOver(Game_Over);
    //     GameOver.setPosition(0, 0);
    //     window.draw(GameOver);
    // }
    window.display();
}

 void Engine::setupText(Text *textItem, const Font &font, const String &value, int size, Color colour){
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(colour);
}

void Engine::newSnake(){
        snake.clear();
        snake.emplace_back(Vector2f(100, 100));
        snake.emplace_back(Vector2f(80, 100));
        snake.emplace_back(Vector2f(60, 100));
}

void Engine::addSnakeSection(){
    Vector2f newSectionPosition = snake[snake.size()-1].getPosition();
    snake.emplace_back(newSectionPosition);
}

void Engine::moveApple(){
    //find the location to place apple
    // must not be inside the apple

   // Vector2f appleResolution = Vector2f(resolution.x/20 -2, resolution.y /20 -2);
    Vector2f newAppleLocation;

    bool badLocation = false;
    srand(time(nullptr));
    //loop until find a valid location
    do {
        badLocation = false;
        //generate a random location
        newAppleLocation.x = (rand() % ((int)resolution.x/20)) * 20;
        newAppleLocation.y = (rand() % ((int)resolution.y/20)) * 20;

        // newAppleLocation.x =  (int) (1+ rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) * 20;
        // newAppleLocation.y =  (int) (1+ rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) * 20;
    for (auto & s : snake){
        if(s.getShape().getGlobalBounds()
            .intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))){
                badLocation = true;
                break;
            }
        }//check that apple on the wall or not
    for(auto & w : wallSection){
        if(w.getShape().getGlobalBounds()
            .intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))){
                badLocation = true;
                break;
            }
    }
    } while (badLocation);
    apple.setPosition(newAppleLocation);
}

//check the level manifest file and make sure that we can open each level file
void Engine::checkLevelFiles(){
    ifstream levelManifest("levels/levels.txt");
    ifstream testFile;

    for(string nameLevelLine; getline(levelManifest, nameLevelLine);){
        //check that we can open the level file 
        testFile.open("levels/" + nameLevelLine);
        if(testFile.is_open()){
            //the level file open, lets add it to the list of available levels
            levels.emplace_back("levels/" + nameLevelLine);
            testFile.close();
            maxLevel++;
        }
    }
}

void Engine::loadLevel(int levelNumber){
    string levelFile = levels[levelNumber-1];
    ifstream level(levelFile);
    string line;
    if(level.is_open()){
        for(int y=0;y < 40; y++){
            
            getline(level, line);
            
            for(int x=0;x<60;x++){
                if(line[x] == 'x'){
                    wallSection.emplace_back(Wall(Vector2f(x * 20, y * 20), Vector2f(20, 20)));
                }
            }
        }
    }
    level.close();
}

void Engine::beginNextLevel(){
    currentLevel += 1;
    wallSection.clear();
    directionQueue.clear();
    speed = 10 + currentLevel*2;

    SnakeDirection = Direction::RIGHT;
    sectionToAdd = 0;
    appleEatenThisLevel = 0;

    loadLevel(currentLevel);
    newSnake();
    moveApple();
    currentLevelText.setString("level " + to_string(currentLevel));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    // appleEatenText.setPosition(
    //     Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width + 20, -9));
}



void Engine::togglePause(){
    if(currentGameState == GameState::RUNNING || currentGameState == GameState::WINNING ){

        lastGameState = currentGameState;
        currentGameState = GameState::PAUSED;
    }
    else if(currentGameState == GameState::PAUSED ){
        currentGameState = lastGameState;
    }

   
   
}

