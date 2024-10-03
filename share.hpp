#ifndef SHARE_HPP
#define SHARE_HPP
//standar libraries
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
//user libraries
#include "game.hpp"
#include "input.hpp"
#include "gameWorld.hpp"

extern sf::RenderWindow sf_window;
extern sf::Event sf_event;
extern class CGame *pgame;
extern class CWorld *pworld;

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define GRID_SIZE 50

#endif //SHARE_HPP
