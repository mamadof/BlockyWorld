#include "share.hpp"

CGame *pgame;
CWorld *pworld;
CPlayer *pplayer;
sf::RenderWindow sf_window;
sf::Event sf_event;
static char buff[100];
static sf::Clock frameClock;
sf::RectangleShape blockShadow;

void CGame::run()
{
    init();
    while(sf_window.isOpen())
    {
        while(sf_window.pollEvent(sf_event))
        {
            if(sf_event.type == sf::Event::Closed)
            {
                close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q))
        {
            close();
        }
        Input::handleInput();
        tick();
        pworld->tick();
        render();
    }
}


void CGame::init()
{
    //width and height don't matter anyway
    sf_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BlockyWorld");
    sf_window.setFramerateLimit(60);
    m_font.loadFromFile("data/fonts/roboto.ttf");
    m_debugText.setFont(m_font);
    m_debugText.setCharacterSize(20);
    m_debugText.setPosition(0,0);
    m_debugText.setFillColor(sf::Color::Black);
    //set the world pointer
    pworld = new CWorld();
    //set default game key bindings
    Input::setKeyBind(Input::GameKeys::JUMP, sf::Keyboard::Scancode::Space);
    Input::setKeyBind(Input::GameKeys::A, sf::Keyboard::Scancode::A);
    Input::setKeyBind(Input::GameKeys::D, sf::Keyboard::Scancode::D);
    Input::setKeyBind(Input::GameKeys::W, sf::Keyboard::Scancode::W);
    Input::setKeyBind(Input::GameKeys::S, sf::Keyboard::Scancode::S);
    Input::setKeyBind(Input::GameKeys::LMB, sf::Mouse::Left, true);
    Input::setKeyBind(Input::GameKeys::RMB, sf::Mouse::Right, true);
    //create player
    pplayer = new CPlayer();
    pworld->setPlayer(pplayer);
    //game border
    m_border.setSize(sf::Vector2f(MAX_BLOCKS*GRID_SIZE, MAX_BLOCKS*GRID_SIZE));
    m_border.setPosition(sf::Vector2f(0,0));
    m_border.setFillColor(sf::Color(0,255,100,60));
    m_border.setOutlineThickness(3);
    m_border.setOutlineColor(sf::Color(255,0,0,255));
    //block
    blockShadow.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE));
    blockShadow.setFillColor(sf::Color(0,0,60,30));

}

void CGame::tick()
{
    m_mousePos = sf::Mouse::getPosition(sf_window);
    m_mousePosWorld = sf::Vector2i(sf_window.mapPixelToCoords(m_mousePos));
    sf_window.setView(pplayer->m_view);
    //debug
    m_debugString.clear();
    sprintf(buff, "FPS:%f\n", 1/frameClock.restart().asSeconds());
    m_debugString.append(buff);
    sprintf(buff, "m_mousepos:%d, %d\n", m_mousePos.x, m_mousePos.y);
    m_debugString.append(buff);
    sprintf(buff, "m_mousePosWorld:%d, %d\n", m_mousePosWorld.x, m_mousePosWorld.y);
    m_debugString.append(buff);
    m_debugText.setString(m_debugString);
    m_debugText.setPosition(sf::Vector2f(sf_window.mapPixelToCoords(sf::Vector2i(0,0))));
    //block shadow
    blockShadow.setPosition(sf::Vector2f(snapToGrid(m_mousePosWorld)));
}

void CGame::render()
{
    sf_window.clear(sf::Color::White);
    //draw player
    sf_window.draw(m_border);
    //draw border
    sf_window.draw(pplayer->m_body);
    //draw blocks
    CBlock* pblock;
    for (int x = 0; x < MAX_BLOCKS; x++)
    {
        for (int y = 0; y < MAX_BLOCKS; y++)
        {
            pblock = pworld->blockByArray(x, y);
            if (pblock == NULL)continue;
            sf_window.draw(pblock->m_body);
        }
    }
    //block shadow
    sf_window.draw(blockShadow);
    //debuging stuff
    sf_window.draw(m_debugText);
    sf_window.display();
}

void CGame::close()
{
    sf_window.close();
}

//helper functions
sf::Vector2i snapToGrid(int x, int y)
{
    return sf::Vector2i(((int)x / GRID_SIZE)*GRID_SIZE,((int)y / GRID_SIZE)*GRID_SIZE);
}
sf::Vector2i snapToGrid(sf::Vector2i vec2i)
{
    return snapToGrid(vec2i.x, vec2i.y);
}
sf::Vector2i snapToGrid(sf::Vector2f vec2f)
{
    return snapToGrid(vec2f.x, vec2f.y);
}

