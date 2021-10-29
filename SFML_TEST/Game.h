#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
/*
* 
* Class to be used s game engine wrapper class
*/

class Game
{
public:
	// Constructor / Destructor
	Game();
	virtual~Game();

	// Acessorss	
	const bool running()const;

	//functions
	void pollEvents();
	void update();
	void render();

private:

	// variables
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	
	// private functions

	void intiializeVariables();
	void initWindow();


};
	


