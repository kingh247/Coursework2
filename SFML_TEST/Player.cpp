#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 1.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	// load a texture from file
	if (!this->texture.loadFromFile("Textures/ships.png"))
	{

		std::cout << "ERROR::PLAYER INITTEXTURE:: Could not load the texture file." << "\n";
	}

}

void Player::initSprite()
{

	// set texture of sprite
	this->sprite.setTexture(this->texture);

	//resize this sprite
	this->sprite.scale(0.1f, 0.1f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);

}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

void Player::update()
{
	this->updateAttack();

}

void Player::render(sf::RenderTarget& target)
{

	target.draw(this->sprite);
}
