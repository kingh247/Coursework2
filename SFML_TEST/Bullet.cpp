#include "Bullet.h"



void Bullet::initTexture()
{
	// load a texture from file
	if (!this->texture.loadFromFile("Textures/bullet.png"))
	{

		std::cout << "ERROR::Bullet INITTEXTURE:: Could not load the texture file." << "\n";
	}

}

void Bullet::initSprite()
{

	// set texture of sprite
	this->sprite.setTexture(this->texture);
	
	//resize this sprite
	this->sprite.scale(0.1f, 0.1f);
}

Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed)
{

	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(posX, posY);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;
	
}



Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Bullet::update()
{

	//Movement
	this->sprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);

}
