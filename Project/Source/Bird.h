#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bird
{



public:
	Bird(sf::Vector2u windowSize);
	~Bird();
	enum State { Jumping, Free, StayTop, Paused, WaitingTap,onlyAnimate};
	sf::Sprite birdSprite;
	void Update(float deltaTime, float totalTime, sf::RenderWindow& window);
	void Jump();
	State state = State::onlyAnimate;
	sf::FloatRect getBirdRect() {
		return (sf::FloatRect)birdSprite.getGlobalBounds();
	}

	void resetBird(State _state);
	

private:
	std::vector<sf::Texture> flying;

	sf::Vector2f startPosSaver;
	float totalTime;
	float fallSpeed = 9.8f*50.0f;

	void AnimateBird();

	sf::Texture DoTapBitchTexture;
	sf::Sprite DotapBitch;

	float animationSpeed = 0.1f;
	float animateTimer;
	bool haveTimer;
	int currentAnimationFrame = 0;

	float jumpHeight = 125.0f;
	float jumpTo = 0;
	float jumpSpeed = 1000.0f;

	float stayValue = 0.05f;
	float stayUntil;

	float rotationSpeed = 480.0f;

	float fallTimer = 0.8f;
	float fallTime = 0;
	bool isFalling;
	
	float Lerp(float from, float To, float percentTo);
};


