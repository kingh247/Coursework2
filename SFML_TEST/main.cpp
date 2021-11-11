/*
* Group: J2C2)
* Course work 2
* Computer Science Yr2
* Version 1
*
*/
#include <iostream>
#include "Game.h"
#include <time.h> 


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Game game;

    game.run();

    return 0;
}