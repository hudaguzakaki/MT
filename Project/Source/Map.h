#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map 
{
public:
	Map(sf::Vector2u windowSize, int _highScore);
	~Map();
	void Update(float deltaTime, float totalTime, sf::RenderWindow& window);
	int isColliding(sf::FloatRect birdRect);
	void spawnPipes(sf::Vector2u);
	void resetMap();
	int getScore() { return score; }
	bool Paused = false;
	bool inGame = false;
	void setNewHighScore(int newHighScore) {
		highScore = newHighScore;
	}
	
private:

	struct offset {
		int posY;
		float radius;
	};

	int highScore;
	int score;
	sf::Text scoreText;
	sf::Font font;
	std::vector<sf::Sprite> bg;
	std::vector<sf::Sprite> ground;
	std::vector<sf::Sprite> pipes;
	sf::Sprite  pipeSpritePrefab;
	sf::Texture PipeTexture;
	sf::Texture bgTexture;
	sf::Texture groundTexture;
	sf::Texture newHSTexture;
	sf::Sprite newHS;
	float offsetPipeSpawnX = 150.0f;
	bool checkView(sf::FloatRect viewRect, sf::Sprite rectSprite);
	bool pipesSpawned = false;
	float offsetLimiter = 170;
	sf::Vector2f getNewYPos(sf::Vector2u);

	float speed = 200.0f;
};

