
all:
	g++ -IC:\Users\DELL\Documents\mycode\SFML-2.5.1\include -LC:\Users\DELL\Documents\mycode\SFML-2.5.1\lib -o main main.cpp engine.cpp wall.cpp snake.cpp apple.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-Audio
	
	