links = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lGL

all:
	g++ *.cpp imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui-sfml/imgui-SFML.cpp imgui/imgui_demo.cpp -o out $(links)

imgui-a:
	g++ -c imgui/imgui.cpp imgui/imgui_widgets.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui-sfml/imgui-SFML.cpp $(links)
	ar cr imgui.a *.o
	rm *.o

part:
	g++ *.cpp imgui/imgui_demo.cpp imgui.a -o out $(links)