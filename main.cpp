#include "share.hpp"
#include "game.hpp"

extern CGame* pgame;

int main(int argc, char** argv)
{
    pgame = new CGame;
    pgame->run();
    return EXIT_SUCCESS;
}