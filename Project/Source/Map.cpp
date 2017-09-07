#include "Map.h"
#include <iostream>
#include <random>
#include <math.h>


Map::Map(sf::Vector2u windowSize, int _highScore) {
	srand(time(NULL));
	highScore = _highScore;
	bgTexture.loadFromFile("images/bg.png");
	//bgTexture.setSmooth(true);
	sf::Sprite bgTempSprite;
	bgTempSprite.setTexture(bgTexture);
	bgTempSprite.setScale(sf::Vector2f(float(windowSize.x / bgTempSprite.getLocalBounds().width), float(windowSize.y / bgTempSprite.getLocalBounds().height)));
	bgTempSprite.setPosition(0, 0);
	//bg.setOrigin(birdSprite.getLocalBounds().width / 2, birdSprite.getLocalBounds().width / 2);
	bg.push_back(bgTempSprite);
	bgTempSprite.move(bgTempSprite.getGlobalBounds().width-1, 0);
	bg.push_back(bgTempSprite);

	newHSTexture.loadFromFile("images/new.png");
	newHS.setTexture(newHSTexture);
	newHS.setOrigin(newHS.getGlobalBounds().width / 2, newHS.getGlobalBounds().height / 2);
	newHS.setScale(2.0f, 2.0f);
	newHS.setPosition(100, 35);
	
	font.loadFromFile("fonts/flappyBird.ttf");
	scoreText.setFont(font);
	scoreText.setString(std::to_string(score));
	scoreText.setCharacterSize(60);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setOutlineColor(sf::Color::Black);
	scoreText.setOutlineThickness(1.5f);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition(25, 10);



	groundTexture.loadFromFile("images/ground.png");
	//groundTexture.setSmooth(true);
	sf::Sprite groundTempSprite;
	groundTempSprite.setTexture(groundTexture);
	groundTempSprite.setScale(2.0f, 2.0f);
	groundTempSprite.setPosition(0, (17 - 3)*windowSize.y / 17);
	ground.push_back(groundTempSprite);
	groundTempSprite.move(groundTempSprite.getGlobalBounds().width - 1, 0);
	ground.push_back(groundTempSprite);
	
	PipeTexture.loadFromFile("images/pipe.png");

	pipeSpritePrefab.setTexture(PipeTexture, true);
	pipeSpritePrefab.setOrigin(pipeSpritePrefab.getGlobalBounds().width / 2, pipeSpritePrefab.getGlobalBounds().height / 2);
	pipeSpritePrefab.setScale(3.0f, 3.0f);
}

sf::Vector2f Map::getNewYPos(sf::Vector2u windowSize) {
	
	int topLimiter = 0 + offsetLimiter;
	int bottomLimiter = ground[0].getPosition().y - offsetLimiter;

	int randNum = rand() % (bottomLimiter - topLimiter + 1) + topLimiter;
	offset offSet;
	offSet.posY = randNum;
	offSet.radius = 125;

	auto newYPos1 = offSet.posY + offSet.radius + pipeSpritePrefab.getGlobalBounds().height / 2;
	auto newYPos2 = offSet.posY - offSet.radius - pipeSpritePrefab.getGlobalBounds().height / 2;

	return sf::Vector2f(newYPos1, newYPos2);
}

void Map::resetMap() {
	score = 0;
	pipesSpawned = false;
	scoreText.setString(std::to_string(score));
	pipes.clear();
}

int Map::isColliding(sf::FloatRect birdRect) {
	int isCollided = 0;
	for (std::vector<sf::Sprite>::iterator it = ground.begin(); it != ground.end(); ++it) {
		if ((*it).getGlobalBounds().intersects(birdRect))
			isCollided = 1;
	}

	for (std::vector<sf::Sprite>::iterator it = pipes.begin(); it != pipes.end(); ++it) {
		if ((*it).getGlobalBounds().intersects(birdRect))
			isCollided = 2;
	}
	return isCollided;
}

bool Map::checkView(sf::FloatRect viewRect, sf::Sprite rectSprite) {
	if (viewRect.intersects(sf::FloatRect(rectSprite.getGlobalBounds())))
		return true;
	else
		return false;
}

void Map::spawnPipes(sf::Vector2u windowSize) {
	if (!pipesSpawned) {
		pipeSpritePrefab.setRotation(0);
		sf::Vector2f newYPos = getNewYPos(windowSize);
		pipeSpritePrefab.setPosition(windowSize.x + offsetPipeSpawnX, newYPos.x);
		pipes.push_back(pipeSpritePrefab);

		pipeSpritePrefab.setRotation(180);
		pipeSpritePrefab.setPosition(windowSize.x + offsetPipeSpawnX, newYPos.y);
		pipes.push_back(pipeSpritePrefab);

		newYPos = getNewYPos(windowSize);
		pipeSpritePrefab.setRotation(0);
		pipeSpritePrefab.setPosition(windowSize.x + windowSize.x/2 + offsetPipeSpawnX, newYPos.x);
		pipes.push_back(pipeSpritePrefab);

		pipeSpritePrefab.setRotation(180);
		pipeSpritePrefab.setPosition(windowSize.x + windowSize.x/2 + offsetPipeSpawnX, newYPos.y);
		pipes.push_back(pipeSpritePrefab);
		pipesSpawned = true;

		newYPos = getNewYPos(windowSize);
		pipeSpritePrefab.setRotation(0);
		pipeSpritePrefab.setPosition(windowSize.x*2 + offsetPipeSpawnX, newYPos.x);
		pipes.push_back(pipeSpritePrefab);

		pipeSpritePrefab.setRotation(180);
		pipeSpritePrefab.setPosition(windowSize.x*2 + offsetPipeSpawnX, newYPos.y);
		pipes.push_back(pipeSpritePrefab);
		pipesSpawned = true;
	}
}

void Map::Update(float deltaTime, float totalTime, sf::RenderWindow& window) {
	//ground.getGlobalBounds().intersects(window.getView());
	sf::FloatRect viewRect = sf::FloatRect(window.getViewport(window.getDefaultView()));
	
	for (std::vector<sf::Sprite>::iterator it = bg.begin(); it != bg.end(); ++it) {

		(*it).move(-speed/10 * deltaTime, 0);
		window.draw(*it);
	}

	//endless pipes
	//bidlokoding
	
	for (std::vector<sf::Sprite>::iterator it = pipes.begin(); it != pipes.end(); ++it) {
		if (!Paused) {
			(*it).move(-speed *deltaTime, 0);

			if (!checkView(viewRect, *it) && (*it).getPosition().x < 0) {

				(*it).move(window.getSize().x + window.getSize().x / 2, 0);
				if (std::distance(pipes.begin(), it) % 2 == 0)
				{
					score ++;
					scoreText.setString(std::to_string(score));
					sf::Vector2f newYPos = getNewYPos(window.getSize());
					auto nextIt = std::next(it);
					(*it).setPosition((*it).getPosition().x, newYPos.x);
					(*nextIt).setPosition((*nextIt).getPosition().x, newYPos.y);
				}
			}
		}
		window.draw(*it);
	}
	
	for (std::vector<sf::Sprite>::iterator it = ground.begin(); it != ground.end(); ++it) {
		if (!Paused)
			(*it).move(-speed *deltaTime, 0);
		window.draw(*it);
	}

	//make bg endless
	auto itbg = bg.begin();
	if (!checkView(viewRect, *itbg)) {
		auto end = std::prev(bg.end());
		(*itbg).setPosition((*end).getPosition().x + (*end).getGlobalBounds().width, 0);
		std::iter_swap(itbg, end);
	}

	//endless ground
	auto it = ground.begin();
	if (!checkView(viewRect, *it)) {
		auto end = std::prev(ground.end());
		(*it).move((*end).getPosition().x + (*end).getGlobalBounds().width*2, 0);
		std::iter_swap(it, end);
	}

	if (score > highScore) {
		window.draw(newHS);
	}

	if (inGame)
		window.draw(scoreText);
	
}


Map::~Map(){

}
