#pragma once

#include "Game.h"






// constructors
void Game::intiializeVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 600;


	this->window = new sf::RenderWindow(this->videoMode, "CourseWork 2 game 1", sf::Style::Titlebar | sf::Style::Close);
}

// constructors /destructor
Game::Game()
{
	this->intiializeVariables();
	this->initWindow();

}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}


void Game::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
               this-> window->close();
            break;
        }

    }

}

// functions
void Game::update()
{
    this->pollEvents();

}

void Game::render()
{

    this->window->clear(sf::Color(255,0,255));

    this->window->display();
}
