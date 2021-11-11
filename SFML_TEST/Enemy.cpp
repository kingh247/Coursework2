#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand()% 20 + 20);
	this->shape.setPointCount(rand()% 20 + 3);
}

void Enemy::initVariables()
{
	 type = 0;
	 hp = 0; 
	 hpMax = 10;
	 damage = 1;
	 points = 5;
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


//functions
void Enemy::update()
{
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
}

