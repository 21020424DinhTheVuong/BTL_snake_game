
all:
	g++ -Icode\include -Lcode\lib -o main main.cpp engine.cpp wall.cpp snake.cpp apple.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-Audio
	
	