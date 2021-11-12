#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include<iostream>
/*
*
* Class to be used as game engine wrapper class
*/

class Player
{

private:
	sf::Sprite sprite;
	sf::Texture texture;
	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	// private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	// Constructor / Destructor

	Player();
	virtual~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;


	//functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};


#endif // !PLAYER_H
