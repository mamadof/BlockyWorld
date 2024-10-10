#include "info.hpp"
#include "gameWorld.hpp"
#include <SFML/Graphics.hpp>
#include "share.hpp"
#include "game.hpp"
#include <memory.h>

static unsigned long *a_pBlockMaxHP = new unsigned long[Ginfo::Block::TYPE_COUNT];
static Particles *a_pBlockParticles = new Particles[Ginfo::Block::TYPE_COUNT];

void loadInfos()
{

}
unsigned long& getBlockMaxHP(Ginfo::Block::Type type)
{

}
struct particle& getBlockParticle(Ginfo::Block::Type type)
{

}

