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
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Points: ");

	this->endScreenText.setFont(this->font);
	this->endScreenText.setCharacterSize(50);
	this->endScreenText.setFillColor(sf::Color::Red);
	this->endScreenText.setString("Game Over");
	this->endScreenText.setPosition(
		this->window->getSize().x / 2.f - this->endScreenText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->endScreenText.getGlobalBounds().height / 2.f);

	//init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));



	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/space.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
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
	this->initSystems();
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
		this->updatePollEvents();

		if (this->player->getHp() > 0)
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
	std::stringstream ss;
	std::stringstream endScore;

	ss << "Points: " << this->points;
	endScore << "Score: " << this -> points;

	this->pointText.setString(ss.str());
	this->endScreenText.setString("Game Over \n " + endScore.str());

	//update player GUI
	float hpPercent = static_cast<float> ( this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));

	
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	else if (this->player->getBounds().left + this-> player->getBounds().width >= this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x- this->player->getBounds().width, this->player->getBounds().top);
	}

	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y) {
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
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

			//If enemy reaches the bottom of screen take away points
			this->points -= enemies.at(counter)->getPoints();
		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			//Delete the enemy
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			
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

				this->points += enemies[i]->getPoints();

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
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);

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

	//Game over screen
	if (this->player->getHp() <= 0)
		this->window->draw(this->endScreenText);

	this->window->display();

}
