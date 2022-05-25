
all:
	g++ -ISFML-2.5.1\include -LSFML-2.5.1\lib -o main main.cpp engine.cpp wall.cpp snake.cpp apple.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-Audio
	
	