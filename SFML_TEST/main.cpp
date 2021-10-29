/*
* A john kingh
* Course work 2
* Computer Science Yr2 
* Version 1
*   // my video 
*/
#include <iostream>
#include "Game.h"


//using namespace sf;

int main()
{
    // game engine
    Game game;

    
    //Game Loop
    while (game.running())
    {
        //update
        game.update();
        //render
        game.render();

    }
    return 0;
}