all:
	g++ main.cpp player.cpp game.cpp gameWorld.cpp input.cpp -o out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network