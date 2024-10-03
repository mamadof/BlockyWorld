#include "share.hpp"

extern CGame* pgame;

int main(int argc, char** argv)
{
    CGame game;
    pgame = &game;
    pgame->run();
    return EXIT_SUCCESS;
}