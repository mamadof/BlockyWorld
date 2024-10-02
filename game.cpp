#include "share.hpp"

CGame *pgame;
CWorld *pworld;
CPlayer *pplayer;
sf::RenderWindow sf_window;
sf::Event sf_event;

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
        render();
    }
}


void CGame::init()
{
    //width and height don't matter anyway
    sf_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BlockyWorld");
    sf_window.setFramerateLimit(60);
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
}

void CGame::tick()
{
    
}

void CGame::render()
{
    sf_window.clear(sf::Color::White);

    //draw player
    sf_window.draw(pplayer->m_body);

    sf_window.display();
}

void CGame::close()
{
    sf_window.close();
}
