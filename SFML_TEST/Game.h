#pragma once


#include "Player.h"
/*
* 
* Class to be used s game engine wrapper class
*/

class Game
{


private:

	sf::RenderWindow* window;

	//player
	Player* player;
	
	//private functions
	void initWindow();
	void initPlayer();

public:
	// Constructor / Destructor

	Game();
	virtual~Game();

	//functions
	void run();

	void update();
	void render();

};
	


