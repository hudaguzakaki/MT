#pragma once
#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Map.h"
#include "MainMenu.h"
#include "Pause.h"

enum State{Menu,Game,Paused};

class GameApp
{

public:
	GameApp();
	void Run();
	sf::RenderWindow *window;
	sf::Time deltaTime;
	sf::Time totalTime;

private:
	State state = State::Menu;
	bool isDead;
	void restartGame(Bird::State newState);
	sf::Clock deltaClock;
	sf::Clock totalClock;
	Bird *bird;
	Map *map;
	MainMenu *menu;
	Pause *pause;
	void CheckCollides(Bird *bird, Map *map);
};

