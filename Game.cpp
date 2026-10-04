#include "Game.h"


//private functions
void Game::initVariables()
{
	this->window = nullptr;
	this->health = 10;
	this->points = 0;
	this->enemySpawnTime = 0.f;
	this->enemySpawnTimeMax = 10.f;
	this->MaxEnemy=5;
}

void Game::initWindow()
{
	this->videoMode.size.x = 860;
	this->videoMode.size.y = 640;
	this->window = new sf::RenderWindow(this->videoMode, "Game",sf::Style::Default,sf::State::Fullscreen);
	this->window->setFramerateLimit(60);
}
void Game::initEnemies()
{
	this->Enemy.setPosition(sf::Vector2f(10.f, 0.f));
	this->Enemy.setSize(sf::Vector2f(100.f,100.f));
	this->Enemy.setScale(sf::Vector2f(0.5f,0.5f));
	this->Enemy.setFillColor(sf::Color::Magenta);
}

void Game::initShooter()
{
	this->shooter.setRadius(30.f);
	this->shooter.setPosition(sf::Vector2f(500.f, this->window->getSize().y - (this->shooter.getRadius()*2)));
	this->shooter.setFillColor(sf::Color::Cyan);
}

void Game::initLaser()
{
	this->Laser.setPosition(sf::Vector2f(0.f,0.f));
	this->Laser.setSize(sf::Vector2f(5.f,3.f));
	this->Laser.setFillColor(sf::Color::Red);
}

//void Game::initText()
//{
//	this->font.openFromFile(R"(D:\New Learning\Games\Shooter\fonts\Roboto-VariableFont_wdth,wght.ttf)");
//	this->uiText.setFont(this->font);
//	this->uiText.setCharacterSize(12);
//	this->uiText.setPosition(sf::Vector2f(0,0));
//	this->uiText.setFillColor(sf::Color::White);
//	this->uiText.setString("None");
//}



//Constructor-Destructor
Game::Game()
{
	//this->initText();
	clock.start();
	this->initVariables();
	this->initWindow();
	this->initShooter();
	this->initEnemies();
	this->initLaser();
}

Game::~Game(){
	delete this->window;
}


//Accessors
bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}



void Game::spawnEnemies()
{
	sf::Vector2f Position=sf::Vector2f(
		std::rand() % static_cast<int>(this->window->getSize().x - this->Enemy.getSize().x),
		0.f
	);
	this->Enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	int type = rand() % 5;
	switch (type) {
	case 1:
		this->Enemy.setScale(sf::Vector2f(0.3f, 0.3f));
		this->Enemy.setFillColor(sf::Color::Red);
		this->Enemy.setPosition(Position);
		break;
	case 2:
		this->Enemy.setScale(sf::Vector2f(0.4f, 0.4f));
		this->Enemy.setFillColor(sf::Color::Yellow);
		this->Enemy.setPosition(Position);
		break;
	case 3:
		this->Enemy.setPosition(sf::Vector2f(
			std::rand() % static_cast<int>(this->window->getSize().x - this->Enemy.getSize().x),
			100.f
			));
		this->Enemy.setFillColor(sf::Color::Blue);
		break;
	case 4:
		this->Enemy.setPosition(sf::Vector2f(
			std::rand() % static_cast<int>(this->window->getSize().x - this->Enemy.getSize().x),
			150.f
		));
		this->Enemy.setFillColor(sf::Color::White);
		break;
	default:
		this->Enemy.setPosition(Position);
		this->Enemy.setFillColor(sf::Color::Green);
		break;

	}

	this->Enemies.push_back(this->Enemy);
}

//public functions
void Game::pollEvents()
{
	
		this->window->handleEvents(
			[this](const sf::Event::Closed&) {
				this->window->close();
			},
			[this](const sf::Event::KeyPressed& k) {
				if (k.scancode == sf::Keyboard::Scancode::Escape) {
					std::cout << "Escape";
					this->window->close();
				}
			}
		);

}


void Game::moveShooter()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) and this->shooter.getPosition().x < this->window->getSize().x) {
		this->shooter.move(sf::Vector2f(8.f,0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left) and this->shooter.getPosition().x > 0) {
		this->shooter.move(sf::Vector2f(-8.f, 0.f));
	}
}


void Game::shooting()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) and (clock.getElapsedTime()).asMilliseconds() >= 200) {
		this->Laser.setPosition(sf::Vector2f(this->shooter.getPosition().x + this->shooter.getRadius() - 2.5f, this->shooter.getPosition().y - this->shooter.getRadius() - 1));
		this->Lasers.push_back(this->Laser);
		clock.restart();
	}

	//std::cout << "Entering loop\n";
	for (int i = 0; i < this->Lasers.size(); i++)
	{
		//std::cout << "loop Entered";
		this->Lasers[i].move(sf::Vector2f(0.f,-5.f));
		//std::cout << "\nLaser is moving\n";

		if (this->Lasers[i].getPosition().y < 0.f)
		{
			//std::cout<<"deleting Laser\n";
			this->Lasers.erase(this->Lasers.begin() + i);
			--i;
		}
	}
}

//void Game::updateText()
//{
//	std::stringstream ss;
//	ss << "Points: " << this->points;
//	this->uiText.setString(ss.str());
//}



void Game::updateEnemies()
{
	//std::cout << "Updating Enemies\n";
	if (this->Enemies.size() < this->MaxEnemy)
	{	
		//updating timer for spawning enemy
		if (this->enemySpawnTime >= this->enemySpawnTimeMax) {
			this->spawnEnemies();
			this->enemySpawnTime = 0.f;
		}
		else {
			this->enemySpawnTime += 1.f;
		}
	}

	//Enemies moving & player health
	for (int i = 0; i < this->Enemies.size(); i++) {
		this->Enemies[i].move(sf::Vector2f(0.f, 5.f));
		if (this->Enemies[i].getGlobalBounds().contains(this->shooter.getPosition())) {
			if (health == 0) {
				this->window->close();
			}
			else { this->health--; 
				std::cout<<"-1\n";
			}
		}

		//destroying enemies when hit ground
		if (this->Enemies[i].getPosition().y > this->window->getSize().y) {
			this->Enemies.erase(this->Enemies.begin()+i);
			--i;
			//std::cout << "deleting enemy\n";
			continue;
		 }

		//killing enemies with laser
		for (int e = 0; e < this->Lasers.size();e++) {
			if (this->Enemies[i].getGlobalBounds().contains(this->Lasers[e].getPosition())) {
				//std::cout << "Delete\n";
				sf::Color Ecolor = (this->Enemies.begin() + i)->getFillColor();
				this->Enemies.erase(this->Enemies.begin() + i);
				this->Lasers.erase(this->Lasers.begin() + e);
				if (Ecolor ==sf::Color::Blue){
					points = points + 2;
				}
				else if (Ecolor == sf::Color::Red){
					points = points + 5;
				}
				else if (Ecolor == sf::Color::Yellow){
					points = points + 4;
				}
				else if (Ecolor==sf::Color::White){
					points = points + 3;
				}
				else {
					points++;
				}
				--i;
				--e;
				break;
			}

		}
	}
	//std::cout << "Done updating\n";
}

void Game::renderLaser()
{
	//std::cout << "Rendering Laser\n";
	for (auto& j: this->Lasers) {
		this->window->draw(j);
	}
	//std::cout << "Laser rendered\n";
}

//void Game::renderText()
//{
//	this->window->draw(this->uiText);
//}

void Game::renderEnemies()
{
	//std::cout << "Rendering enemies\n";
	for (auto& e : this->Enemies) {
	this->window->draw(e);
	}
	//std::cout << "Done rendering\n";
}

void Game::update()
{
	this->pollEvents();
	this->moveShooter();
	//this->updateText();
	this->shooting();
	this->updateEnemies();
}

void Game::render()
{
	this->window->clear();
	this->window->draw(this->shooter);
	//this->renderText();
	this->renderLaser();
	this->renderEnemies();
	

	this->window->display();
}

