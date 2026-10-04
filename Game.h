#pragma once

#include <iostream>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


class Game
{
private:
	//Variable
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Clock clock;

	//Resourse
	//sf::Font font;
	//sf::Text uiText;

	//Private functions
	void initVariables();
	void initWindow();
	void initEnemies();
	void initShooter();
	void initLaser();
	//void initText();

	unsigned health;
	int points;
	float enemySpawnTime;
	float enemySpawnTimeMax;
	int MaxEnemy;

	//Game objects
	sf::RectangleShape Enemy;
	std::vector<sf::RectangleShape> Enemies;
	std::vector<sf::RectangleShape> Lasers;
	sf::RectangleShape Laser;
	sf::CircleShape shooter;

public:
	//Constructor
	Game();
	//Destructor
	~Game();


	//Accessors
	bool getWindowIsOpen() const;


	//Functions
	void spawnEnemies();
	void pollEvents();
	void moveShooter();
	void shooting();
	//void updateText();
	void updateEnemies();
	//void renderText();
	void renderLaser();
	void renderEnemies();
	void update();
	void render();
};