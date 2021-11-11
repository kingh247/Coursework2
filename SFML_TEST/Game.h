#ifndef GAME_H
#define GAME_H

#include <map>
#include "Player.h"
#include "Bullet.h"
/*
* 
* Class to be used as game engine wrapper class
*/

class Game
{


private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map <std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//player
	Player* player;
	
	
	//private functions
	void initWindow();
	void initTextures();

	void initPlayer();

public:
	// Constructor / Destructor

	Game();
	virtual~Game();

	//functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void update();
	void render();

};
	
#endif // !GAME_H

