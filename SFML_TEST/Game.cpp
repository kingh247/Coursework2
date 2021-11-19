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

void Game::initGUI()
{
	//Load fonts
	if (!this->font.loadFromFile("Fonts/montserrat.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//init point text 
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(12);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/space.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initPlayer()
{
	this->player = new Player();

	
}
void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}
//con/des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
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

	//Delete Enemies
	for (auto* i : this->enemies)
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width/2.f,
		this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{

}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
}

void Game::updateBullets()
{
	int counter = 0;

	for (auto* bullet : this->bullets) {

		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{

			//Delete the bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			//Show how many bullets there currently are
			std::cout << this->bullets.size() << "\n";
		}

		++counter;
	}

}

void Game::updateEnemies()
{
	//spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//update
	int counter = 0;
	for (auto* enemy : this->enemies) {
		enemy->update();

		if (enemy->getBounds().top > this->window->getSize().y)
		{

			//Delete the enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i) {
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++) {
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds())) {
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}



// functions

void Game::update()
{
	this->updatePollEvents();

	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}



void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	// draw stuff
	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {

		bullet->render(this->window);
	}
	for (auto* enemy : this->enemies) {

		enemy->render(this->window);
	}

	this->renderGUI();

	//this->enemy->render(this->window);

	this->window->display();

}
