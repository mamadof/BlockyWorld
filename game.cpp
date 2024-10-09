#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gameWorld.hpp"
#include "game.hpp"
#include "input.hpp"
#include "share.hpp"
#include "math.hpp"

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

CGame *pgame;
CWorld *pworld;
CPlayer *pplayer;
sf::RenderWindow sf_window;
sf::Event sf_event;
static char buff[100];
static sf::Clock frameClock;
sf::RectangleShape blockShadow;
bool temp = true;

void CGame::run()
{
    init();
    ImGui::SFML::Init(sf_window);
    while(sf_window.isOpen())
    {
        while(sf_window.pollEvent(sf_event))
        {
            ImGui::SFML::ProcessEvent(sf_window, sf_event);
            if(sf_event.type == sf::Event::Closed)
            {
                ImGui::SFML::Shutdown();
                close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Q))
        {
            close();
        }
        ImGui::SFML::Update(sf_window, frameClock.getElapsedTime());
        ImGui::ShowDemoWindow();
        // ImGui::ShowDemoWindow(temp);
        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        // if (ImGui::IsWindowHovered())
        // {
        //     printf("hello imgui\n");
        // }
        ImGui::End();

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
    // sf_window.setFramerateLimit(60);
    sf_window.setVerticalSyncEnabled(true);
    m_font.loadFromFile("data/fonts/roboto.ttf");
    m_debugText.setFont(m_font);
    m_debugText.setCharacterSize(20);
    m_debugText.setPosition(0,0);
    m_debugText.setFillColor(sf::Color::Black);
    //set the world pointer
    pworld = new CWorld(10,10);
    //set default game key bindings
    Input::setKeyBind(Input::GameKeys::JUMP, sf::Keyboard::Scancode::Space);
    Input::setKeyBind(Input::GameKeys::A, sf::Keyboard::Scancode::A);
    Input::setKeyBind(Input::GameKeys::D, sf::Keyboard::Scancode::D);
    Input::setKeyBind(Input::GameKeys::W, sf::Keyboard::Scancode::W);
    Input::setKeyBind(Input::GameKeys::S, sf::Keyboard::Scancode::S);
    Input::setKeyBind(Input::GameKeys::ZOOM_IN, sf::Keyboard::Scancode::Equal);
    Input::setKeyBind(Input::GameKeys::ZOOM_OUT, sf::Keyboard::Scancode::Hyphen);
    Input::setKeyBind(Input::GameKeys::LMB, sf::Mouse::Left, true);
    Input::setKeyBind(Input::GameKeys::RMB, sf::Mouse::Right, true);
    //create player
    pplayer = new CPlayer();
    pworld->setPlayer(pplayer);
    //grid indicator for block placement
    blockShadow.setSize(sf::Vector2f(GRID_SIZE,GRID_SIZE));
    blockShadow.setFillColor(sf::Color(0,0,60,30));
    //load textures
    m_aTextures[BLOCK_TEXTURE].loadFromFile("data/images/blocks.png");
    m_aTextures[PLAYER_TEXTURE].loadFromFile("data/images/Peef.png");

    //cover the world with blocks
    // for (int x = 0; x < pworld->m_width/2; x++)
    // for (int y = 0; y < pworld->m_height/2; y++)
    // {
    //     pworld->createBlock(x*GRID_SIZE, y*GRID_SIZE, gt::block::GLASS);
    // }
    
    //make a platform for testing
    for (int x = 0; x < 50; x++)
    {
        pworld->createBlock(x*GRID_SIZE, 6*GRID_SIZE, gt::block::GLASS);
        pworld->createBlock(x*GRID_SIZE, 7*GRID_SIZE, gt::block::GLASS);
        pworld->createBlock(x*GRID_SIZE, 8*GRID_SIZE, gt::block::GLASS);
        pworld->createBlock(x*GRID_SIZE, 9*GRID_SIZE, gt::block::GLASS);
    }
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
    // sprintf(buff, "sizeof sprite:%lu\n", sizeof(m_aSprites[BLOCK_TEXTURE]));
    // m_debugString.append(buff);
    // sf::Vector2f v2f = sf::Vector2f(0,0);
    // sprintf(buff, "distance:%f\n", gm::v2distance(v2f, sf::Vector2f(m_mousePosWorld)));
    // m_debugString.append(buff);

    // CBlock* pblock = pworld->BlockByPos(m_mousePosWorld.x, m_mousePosWorld.y);
    // if(pblock != NULL)
    // {
    //     sprintf(buff, "ID:%lu    ghost:%u     pos:%.0f %.0f\n",
    //     pblock->m_ID, pblock->m_ghost, pblock->m_pos.x, pblock->m_pos.y);
    //     m_debugString.append(buff);
    // }

    m_debugText.setString(m_debugString);
    m_debugText.setPosition(sf::Vector2f(sf_window.mapPixelToCoords(sf::Vector2i(0,0))));
    //block shadow
    blockShadow.setPosition(sf::Vector2f(gm::snapToGrid(m_mousePosWorld)));
}

void CGame::render()
{
    sf_window.clear(sf::Color(100,100,200,0));
    //draw border
    sf_window.draw(pworld->m_border);
    //draw player
    sf_window.draw(pplayer->m_body);
    sf_window.draw(getSprite(gt::entity::PLAYER, pplayer));
    //draw blocks
    CCell* pCell;
    for (int x = 0; x < pworld->m_width; x++)
    {
        for (int y = 0; y < pworld->m_height; y++)
        {
            pCell = pworld->getCell(x*GRID_SIZE, y*GRID_SIZE);
            // sf_window.draw(pCell->m_body);
            CBlock *pblock = &pCell->m_BlockContent;
            if (pblock->m_deleted)continue;
            sf_window.draw(getSprite(gt::entity::BLOCK, pblock));
            //show small blocks if block type is mixed
            if(pblock->m_type == gt::block::MIXED)
            {
                CSmallBlock *pSmallBlock;
                for (int x = 0; x < BLOCK_SUBDIVISION; x++)
                {
                    for (int y = 0; y < BLOCK_SUBDIVISION; y++)
                    {
                        pSmallBlock = &pblock->ma_SmallBlocks[x][y];
                        if (pSmallBlock->m_deleted)continue;
                        sf_window.draw(getSprite(gt::entity::SMALL_BLOCK, pSmallBlock));
                    }
                }
            }
        }
    }
    //block shadow
    sf_window.draw(blockShadow);
    //debuging stuff
    sf_window.draw(m_debugText);
    //imgui stuff
    //draw cells
    ImGui::SFML::Render(sf_window);
    sf_window.display();
}

void CGame::close()
{
    sf_window.close();
}

sf::Sprite &CGame::getSprite(gt::entity::Entity_Type EntityType, void *pEntity)
{
    m_Sprites.setScale(1.f,1.f);
    if (EntityType == gt::entity::BLOCK)
    {
        CBlock *pBlock = (CBlock*)pEntity;
        m_Sprites.setTexture(m_aTextures[BLOCK_TEXTURE]);
        m_Sprites.setTextureRect(sf::IntRect(0,0,BLOCK_SIZE,BLOCK_SIZE));
        m_Sprites.setColor(sf::Color(255,255,255));
        m_Sprites.setPosition(pBlock->m_body.getPosition());
        return m_Sprites;
    }

    if (EntityType == gt::entity::SMALL_BLOCK)
    {
        CSmallBlock *pSmallBlock = (CSmallBlock*)pEntity;
        m_Sprites.setTexture(m_aTextures[BLOCK_TEXTURE]);
        m_Sprites.setTextureRect(sf::IntRect(0,0,BLOCK_SIZE,BLOCK_SIZE));
        m_Sprites.setColor(sf::Color(255,255,255));
        m_Sprites.setScale(1/9.f,1/9.f);
        m_Sprites.setPosition(pSmallBlock->m_body.getPosition());
        return m_Sprites;
    }

    if (EntityType == gt::entity::ITEM)
    {

    }

    if (EntityType == gt::entity::MOB)
    {

    }

    if (EntityType == gt::entity::PLAYER)
    {
        CPlayer *pPlayer = (CPlayer*)pEntity;
        m_Sprites.setTexture(m_aTextures[PLAYER_TEXTURE]);
        m_Sprites.setTextureRect(sf::IntRect(0,0,PLAYER_SPRITE_SIZE,PLAYER_SPRITE_SIZE));
        m_Sprites.setOrigin(sf::Vector2f((float)(PLAYER_SPRITE_SIZE-PLAYER_SIZE)/2,
        (float)(PLAYER_SPRITE_SIZE-PLAYER_SIZE)/2));
        m_Sprites.setPosition(pPlayer->m_body.getPosition());
        return m_Sprites;
    }
}
