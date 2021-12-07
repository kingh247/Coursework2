#include "Enemy.h"



void Enemy::initVariables()
{
	 this ->pointcount= rand() % 8 + 3; // min= 3 max = 10 
	 this ->type = 0;
	 this->hp = this->hpMax;
	 this->hpMax = static_cast<int>(this->pointcount);
	 this->damage = this->pointcount;
	 this->points = this->pointcount;
	 this->speed = static_cast<float>(this->pointcount/3);
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointcount * 5);
	this->shape.setPointCount(this->pointcount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	
	this->initVariables(); 
	this->initShape();

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

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
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

