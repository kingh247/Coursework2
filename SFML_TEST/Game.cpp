#pragma once

#include "Game.h"


//private functions
void Game::initWindow()
{
	
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "CourseWork 2 Game ", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

//private functions

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initPlayer()
{
	this->player = new Player();
}
//con/des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete Textures
	for (auto& i : this->textures) 
	{
		delete i.second;
	}

	//Delete Bullets
	for (auto* i : this->bullets) 
	{
		delete i;
	}
}
// functions
void Game::run()
{
	while (this->window->isOpen()) 
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{

	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 1.f, 1.f, 2.f));
	}
}

void Game::updateBullets()
{
	for (auto *bullet : this->bullets) {

		bullet->update();
	}

}



// functions

void Game::update()
{
	this->updatePollEvents();
	this->updateInput();

	this->updateBullets();
	
}

void Game::render()
{
	this-> window->clear();

	// draw stuff
	this->player->render(*this->window);

	for (auto *bullet : this->bullets) {

		bullet->render(this->window);
	}


	this->window->display();
   
}
