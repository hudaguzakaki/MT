#include "GameApp.h"
#include <iostream>

GameApp::GameApp()
{
	//288*2
	//384*2
	window = new sf::RenderWindow(sf::VideoMode(288*2, 384*2), "MyTonaFlappyBird", sf::Style::Titlebar | sf::Style::Close);
	totalTime = totalClock.restart();
	bird = new Bird(window->getSize());
	menu = new MainMenu(window->getSize(),0);
	map = new Map(window->getSize(), menu->getHighScore());
	pause = new Pause(window->getSize(), Pause::State::InMenu);
}

void GameApp::CheckCollides(Bird *bird, Map *map) {
	if (map->isColliding(bird->getBirdRect()) != 0) {
		isDead = true;
		if (map->isColliding(bird->getBirdRect()) == 1) {
			bird->state = Bird::State::Paused;
			pause->setState(Pause::State::DiePaused);
			map->Paused = true;
			state = State::Paused;
			if (menu->CheckScore(map->getScore())) {
				pause->setNewHighScore(map->getScore());
				map->setNewHighScore(map->getScore());
			}
		}
	}
		
}

void GameApp::restartGame(Bird::State newState) {
	isDead = false;
	map->inGame = true;
	map->resetMap();
	bird->resetBird(newState);
}

void GameApp::Run() {
	while (window->isOpen())
	{
		window->clear();
		deltaTime = deltaClock.restart();
		totalTime = totalClock.getElapsedTime();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					switch (state) {
						case State::Menu: {
							if (menu->isClicked(sf::Mouse::getPosition(*window))) {
								isDead = false;
								state = State::Game;
								pause->state = Pause::State::InGame;
								bird->state = bird->Paused;
								map->Paused = false;
								map->inGame = false;
								restartGame(Bird::State::WaitingTap);
							}
							break;
						};
						case State::Game: {
							if (!isDead) {
								bird->Jump();
								if (pause->isClicked(sf::Mouse::getPosition(*window)) == Pause::PressedButton::btnPausePressed) {
									bird->state = Bird::State::Paused;
									pause->setState(Pause::State::Paused);
									map->Paused = true;
									state = State::Paused;
								}
							}
							break;
						};
						case State::Paused: {
							switch (pause->isClicked(sf::Mouse::getPosition(*window))) {
								case Pause::PressedButton::btnPausePressed: {
									//THIS SHIT CANT BE PRESSED
									//JUST GONNA LEAVE IT HERE FOR DEBUG
									break;
								};
								case Pause::PressedButton::btnResumePressed: {
									state = State::Game;
									pause->state = Pause::State::InGame;
									bird->state = Bird::State::Free;
									map->Paused = false;
									break;
								};
								case Pause::PressedButton::btnMenuPressed: {
									restartGame(Bird::State::onlyAnimate);
									map->inGame = false;
									state = State::Menu;
									pause->state = Pause::State::InMenu;
									break;
								};
								case Pause::PressedButton::btnStartNewPressed: {
									state = State::Game;
									pause->state = Pause::State::InGame;
									restartGame(Bird::State::WaitingTap);
									map->Paused = false;
									break;
								};
							};
							break;
						};
					}

				}
			}

		}

		if (bird->state != Bird::State::WaitingTap) {
			map->spawnPipes(window->getSize());
		}

		map->Update(deltaTime.asSeconds(), totalTime.asSeconds(), *window);
		bird->Update(deltaTime.asSeconds(), totalTime.asSeconds(), *window);
		window->draw(*pause);
		CheckCollides(bird, map);
		
		switch (state) {
			case State::Menu: {
				window->draw(*menu);
				break;
			};
		}

		window->display();
	}
}
