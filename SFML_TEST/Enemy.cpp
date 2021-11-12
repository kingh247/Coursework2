#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand()% 20 + 20);
	this->shape.setPointCount(rand()% 20 + 3);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

void Enemy::initVariables()
{
	 type = 0;
	 hp = 0; 
	 hpMax = 10;
	 damage = 1;
	 points = 5;
	 speed = 5.f;
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initShape();
	this->initVariables(); 
	this->shape.setPosition(pos_x, pos_y); 
}

Enemy::~Enemy()
{
}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}


//functions
void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}

