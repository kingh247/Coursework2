#include "Player.h"

void Player::initTexture()
{
	// load a texture from file
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		
		std::cout << "ERROR::PLAYER INITTEXTURE:: Could not load the texture file." << "\n";
	}

}

void Player::initSprite()
{

	// set texture of sprite
	this->sprite.setTexture(this->texture);

	//resize this sprite
	this->sprite.scale(0.1f,0.1f);
}

Player::Player()
{
	this->movementSpeed =1.f;
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed*dirX, this->movementSpeed * dirY);

}

void Player::update()
{

}

void Player::render(sf::RenderTarget& target)
{

	target.draw(this->sprite);
}
