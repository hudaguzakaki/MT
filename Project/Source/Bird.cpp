#include "Bird.h"

Bird::Bird(sf::Vector2u windowSize) {

	sf::Texture birdTexture;
	for (int i = 0; i < 8; i++) {
		birdTexture.loadFromFile("images/birdAnimation/"+ std::to_string(i) +".png");
		flying.push_back(birdTexture);
	}

	birdSprite.setTexture(flying[currentAnimationFrame]);

	birdSprite.setScale(0.05f, 0.05f);
	birdSprite.setOrigin(birdSprite.getLocalBounds().width/2, birdSprite.getLocalBounds().height / 2);
	birdSprite.setPosition(windowSize.x / 6, windowSize.y / 3);
	birdSprite.setRotation(-20);

	startPosSaver = sf::Vector2f(windowSize.x / 6, windowSize.y / 3);
	DoTapBitchTexture.loadFromFile("images/waitingTap.png");
	DotapBitch.setTexture(DoTapBitchTexture);
	DotapBitch.setOrigin(DotapBitch.getGlobalBounds().width / 2, DotapBitch.getGlobalBounds().height / 2);
	DotapBitch.setScale(4, 4);
	DotapBitch.setPosition(windowSize.x / 2, 3*windowSize.y / 5);
}

void Bird::AnimateBird() {
	if (haveTimer) {
		if (totalTime > animateTimer) {
			currentAnimationFrame++;
			currentAnimationFrame = currentAnimationFrame % 8;	
			birdSprite.setTexture(flying[currentAnimationFrame]);
			haveTimer = false;
		}
	}
	else {
		animateTimer = totalTime + animationSpeed;
		haveTimer = true;
	}
}

void Bird::Jump() {
	jumpTo = birdSprite.getPosition().y - jumpHeight;
	state = State::Jumping;
}

void Bird::resetBird(State _state) {
	state = _state;
	birdSprite.setRotation(-20);
	birdSprite.setPosition(startPosSaver);
}


void Bird::Update(float deltaTime, float _totalTime, sf::RenderWindow& window) {
	
	
	totalTime = _totalTime;

	fallTime += deltaTime;
	if (fallTime > fallTimer) {
		isFalling = true;
		fallTime = 0;
	}
	

	switch (state) {
		case State::Jumping: {
			AnimateBird();
			float jumpPercent = jumpTo/birdSprite.getPosition().y;

			if (jumpPercent < 1) {
				birdSprite.setRotation(-20);
				birdSprite.move(0,-jumpSpeed * deltaTime);
			} else {
				state = State::StayTop;
				stayUntil = totalTime + stayValue;
				
			}
			
			break;
		};
		case State::WaitingTap: {
			AnimateBird();
			window.draw(DotapBitch);
			break;
		};
							 

		case State::StayTop: {
			AnimateBird();
			isFalling = false;
			fallTime = 0;
			if (totalTime > stayUntil) {
				state = State::Free;
			}
			break;
		}
		case State::Free: {
			AnimateBird();
			birdSprite.move(0, fallSpeed * deltaTime);
			fallTime += deltaTime;
			if ((birdSprite.getRotation() <= 90 || birdSprite.getRotation() >= 270) && isFalling) {
				birdSprite.rotate(rotationSpeed * deltaTime);
			}
				
			break;
		};
		case State::onlyAnimate: {
			AnimateBird();
			break;
		};
		case State::Paused: {
			break;
		}
	}

	window.draw(birdSprite);
}

float Bird::Lerp(float from, float to, float percentTo) {
	//std::cout << from + percentTo * (to - from) << std::endl;
	return (from + percentTo * (to - from));
	
}

Bird::~Bird() {

}
