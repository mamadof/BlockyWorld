all:
	g++ main.cpp game.cpp world.cpp input.cpp block.cpp player.cpp entity.cpp -o out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network