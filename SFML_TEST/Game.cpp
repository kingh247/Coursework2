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
void Game::initPlayer()
{
	this->player = new Player();
}
//con/des
Game::Game()
{
	this->initWindow();
	this->initPlayer();
}

Game::~Game()
{
	delete this->window;
	delete this->player;
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



// functions

void Game::update()
{
	sf::Event ev;	
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			this->window->close();
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);
}

void Game::render()
{
	this-> window->clear();

	// draw stuff
	this->player->render(*this->window);

	this->window->display();
   
}
