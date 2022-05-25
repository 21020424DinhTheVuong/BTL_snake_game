#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Graphics/RectangleShape.hpp>
#include<SFML/Audio.hpp>
#include "engine.h"
#include"wall.h"
#include "snake.h"
#include "apple.h"
#include<vector>
#include<deque>
#include<ctime>
#include<string>
#include<fstream>


using namespace sf;
using namespace std;

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

//const Time Engine::TimePerFrame = seconds(1.f/60.f);

#define Max_main_menu 3

class MainMenu{

public:
    MainMenu(float width, float height){
        font.loadFromFile("PixellettersFull.ttf");
        bground.loadFromFile("image/bg.png");
        spriteBground.setTexture(bground);
        spriteBground.setPosition(0, 0);

        


        mainMenu[0].setFont(font);
        mainMenu[0].setFillColor(Color::Blue);
        mainMenu[0].setString("Play");
        mainMenu[0].setCharacterSize(120);
        mainMenu[0].setPosition(370, 230);

        // mainMenu[1].setFont(font);
        // mainMenu[1].setFillColor(Color::Red);
        // mainMenu[1].setString("Options");
        // mainMenu[1].setCharacterSize(70);
        // mainMenu[1].setPosition(400, 430);

        mainMenu[1].setFont(font);
        mainMenu[1].setFillColor(Color::Red);
        mainMenu[1].setString("About");
        mainMenu[1].setCharacterSize(120);
        mainMenu[1].setPosition(370, 350);

        mainMenu[2].setFont(font);
        mainMenu[2].setFillColor(Color::Red);
        mainMenu[2].setString("Exit");
        mainMenu[2].setCharacterSize(120);
        mainMenu[2].setPosition(370, 470);

        MainMenuSelected = -1;
        
        
    }

    void draw(RenderWindow& window){

        window.draw(spriteBground);
        
        for(int i=0; i<Max_main_menu ;++i){
            window.draw(mainMenu[i]);
        }
    }
    void MoveUp(){
        if(MainMenuSelected -1 >= 0){
            mainMenu[MainMenuSelected].setFillColor(Color::Red);

            MainMenuSelected--;

            if(MainMenuSelected == -1){
                MainMenuSelected = 2;
            }
            mainMenu[MainMenuSelected].setFillColor(Color::Blue);

        }
    }
    void MoveDown(){
        if(MainMenuSelected + 1 <= Max_main_menu){
            mainMenu[MainMenuSelected].setFillColor(Color::Red);
            MainMenuSelected++;
            if(MainMenuSelected == 3){
                MainMenuSelected = 0;
            }
            mainMenu[MainMenuSelected].setFillColor(Color::Blue);
        }
    }

    int MainMenuPressed(){
        return MainMenuSelected;
    }
    ~MainMenu(){

    }
private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
    Texture bground;
    Sprite spriteBground;
    
};

int main()
{
    RenderWindow MENU(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!", Style::Default);
    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);
    
    SoundBuffer bufferMenu;
    Sound soundMenu;
    bufferMenu.loadFromFile("music.wav");
    soundMenu.setBuffer(bufferMenu);
    soundMenu.play();
    while (MENU.isOpen())
    {
        
        Event event;
        while (MENU.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                MENU.close();
            }
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Escape) MENU.close();
            }
            if(event.type == Event::KeyReleased)
            {
                if(event.key.code == Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }
                if(event.key.code == Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }
                if(event.key.code == Keyboard::Enter) {
                    

                    int x = mainMenu.MainMenuPressed();
                    if(x == 0) 
                    {   
                        soundMenu.pause();
                        Engine game;

                        game.GameRun();
                        soundMenu.play();
                    }

                   

                    if(x == 1)
                    {   
                        
                        RenderWindow About(VideoMode(1200, 800), "About");

                        while(About.isOpen())
                        {
                            
                            Event aevent;
                            while(About.pollEvent(aevent))  {
                                if(aevent.type == Event::Closed)
                                {
                                    About.close();
                                    
                                }
                                if(aevent.type == Event::KeyPressed){
                                    if(aevent.key.code == Keyboard::Escape) {
                                        About.close();
                                        
                                    }
                                }
                            }
                            Texture about;
                            Sprite spriteAbout;
                            about.loadFromFile("image/about.png");
                            spriteAbout.setTexture(about);
                            spriteAbout.setPosition(0,0);
                            
                            About.clear();
                            About.draw(spriteAbout);
                            About.display();
                        }
                    }

                    if(x == 2)
                        MENU.close();

                    break;             
                }
            }
        }
        MENU.clear();
        mainMenu.draw(MENU);
        MENU.display();
    
        
    }
    
}
// int main(int argc, char** argv){
    
//     Engine game;
//     game.GameRun();

//     return 0;
// }