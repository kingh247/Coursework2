#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include<iostream>
/*
*
* Class to be used s game engine wrapper class
*/

class Player
{

private:
	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed;

	// private functions
	void initTexture();
	void initSprite();

public:
	// Constructor / Destructor

	Player();
	virtual~Player();

	//functions
	void move(const float dirX, const float dirY);
	void update();
	void render(sf::RenderTarget& target);
};
