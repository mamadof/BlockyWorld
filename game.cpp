#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gameWorld.hpp"
#include "game.hpp"
#include "input.hpp"
#include "share.hpp"
#include "math.hpp"
#include "texture.hpp"

#include "imgui-sfml/imgui-SFML.h"
#include "gui.hpp"

CGame *pgame;
CWorld *pworld;
CPlayer *pPlayer;
sf::RenderWindow sf_window;
static char buff[1000];
static sf::Clock frameClock;
static sf::Clock imguiUpdater;
sf::RectangleShape blockShadow;
bool temp = true;
float tempf = 0;

void CGame::run()
{
    init();
    while (sf_window.isOpen() && !isKeyPressed(Input::QUIT))
    {
        handleInput();
        tick();
    }
}

void CGame::init()
{
    //width and height don't matter anyway
    sf_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BlockyWorld");
    //gui stuff
    ImGui::SFML::Init(sf_window);

    loadTextures();
    //initilize all entities infos
    loadInfos();
    // sf_window.setFramerateLimit(0);
    sf_window.setVerticalSyncEnabled(true);
    m_font.loadFromFile("data/fonts/roboto.ttf");
    m_debugText.setFont(m_font);
    m_debugText.setCharacterSize(20);
    m_debugText.setPosition(0,0);
    m_debugText.setFillColor(sf::Color::Black);
    //set the world pointer
    pworld = new CWorld(1000,20);
    //set default game key bindings
    setKeyBind(Input::GameKeys::QUIT, sf::Keyboard::Scancode::Q, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::JUMP, sf::Keyboard::Scancode::Space, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::A, sf::Keyboard::Scancode::A, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::D, sf::Keyboard::Scancode::D, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::W, sf::Keyboard::Scancode::W, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::S, sf::Keyboard::Scancode::S, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::ZOOM_IN, sf::Keyboard::Scancode::Equal, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::ZOOM_OUT, sf::Keyboard::Scancode::Hyphen, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::PLAYER_INVENTORY, sf::Keyboard::Scancode::E, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::REGEN_WORLD, sf::Keyboard::Scancode::R, Input::KEYBOARD);
    setKeyBind(Input::GameKeys::LMB, sf::Mouse::Left, Input::MOUSE);
    setKeyBind(Input::GameKeys::RMB, sf::Mouse::Right, Input::MOUSE);
    setKeyBind(Input::GameKeys::TOOLBAR_NEXT, Input::SCROLL_UP, Input::MOUSE_WHEEL);
    setKeyBind(Input::GameKeys::TOOLBAR_PREV, Input::SCROLL_DOWN, Input::MOUSE_WHEEL);
    //create player
    pPlayer = new CPlayer();
    pworld->setPlayer(pPlayer);
    //grid indicator for block placement
    blockShadow.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE));
    blockShadow.setFillColor(sf::Color(0,0,60,30));


    //cover the world with blocks
    // for (int x = 0; x < pworld->m_width/2; x++)
    // for (int y = 0; y < pworld->m_height/2; y++)
    // {
    //     pworld->createBlock(x*GRID_SIZE, y*GRID_SIZE, gt::block::GLASS);
    // }
    
    //make a platform for testing

    pworld->generateWorld();
}

void CGame::tick()
{
    ImGui::SFML::Update(sf_window, imguiUpdater.getElapsedTime());
    pworld->tick();
    GGUI::handleGui();
    m_deltaTime = frameClock.restart().asSeconds();

    m_mousePos = sf::Mouse::getPosition(sf_window);
    m_mousePosWorld = sf::Vector2i(sf_window.mapPixelToCoords(m_mousePos));
    sf_window.setView(pPlayer->m_view);
    //debug
    m_debugString.clear();

    sprintf(buff, "FPS:%f\n", 1/m_deltaTime);
    m_debugString.append(buff);
    sprintf(buff, "m_deltaTime:%f\n", m_deltaTime);
    m_debugString.append(buff);
    sprintf(buff, "m_mousepos:%d, %d\n", m_mousePos.x, m_mousePos.y);
    m_debugString.append(buff);
    sprintf(buff, "m_mousePosWorld:%d, %d\n", m_mousePosWorld.x, m_mousePosWorld.y);
    m_debugString.append(buff);
    sprintf(buff, "m_numberOfDropItems:%lu\n", pworld->m_numberOfDropItems);
    m_debugString.append(buff);
    if (pworld->getCell(m_mousePosWorld.x, m_mousePosWorld.y) != NULL)
    {
        sprintf(buff, "DropItems:%lu\n",
        pworld->getCell(m_mousePosWorld.x, m_mousePosWorld.y)->m_DropItems.size());
        m_debugString.append(buff);
    }
    m_debugText.setString(m_debugString);
    m_debugText.setPosition(sf::Vector2f(sf_window.mapPixelToCoords(sf::Vector2i(0,0))));
    //block shadow
    blockShadow.setPosition(gm::snapToGrid(m_mousePosWorld));
    render();
}

void CGame::close()
{
    ImGui::SFML::Shutdown();
    sf_window.close();
}
