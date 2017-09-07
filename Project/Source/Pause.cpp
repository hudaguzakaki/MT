#include "Pause.h"



Pause::Pause(sf::Vector2u windowSize, State _state) {
	state = _state;

	btnPauseTexture.loadFromFile("images/pause.png");
	btnPause.setTexture(btnPauseTexture);

	btnPlayTexture.loadFromFile("images/pausePlay.png");
	btnPlay.setTexture(btnPlayTexture);

	btnMenuTexture.loadFromFile("images/menu.png");
	btnMenu.setTexture(btnMenuTexture);

	btnStartTexture.loadFromFile("images/start.png");
	btnStart.setTexture(btnStartTexture);

	gameOverTexture.loadFromFile("images/gameOver.png");
	gameOver.setTexture(gameOverTexture);

	btnPause.setScale(3, 3);
	btnPause.setPosition(windowSize.x - btnPause.getGlobalBounds().width- 10, 10);

	btnMenu.setOrigin(btnMenu.getGlobalBounds().width / 2, btnMenu.getGlobalBounds().height / 2);
	btnMenu.setScale(3, 3);
	btnMenu.setPosition(windowSize.x / 2 - 75, windowSize.y * 2 / 3);

	btnStart.setOrigin(btnStart.getGlobalBounds().width / 2, btnStart.getGlobalBounds().height / 2);
	btnStart.setScale(3, 3);
	btnStart.setPosition(windowSize.x / 2 + 75, windowSize.y * 2 / 3);

	btnPlay.setOrigin(btnPlay.getGlobalBounds().width / 2, btnPlay.getGlobalBounds().height / 2);
	btnPlay.setScale(3, 3);
	btnPlay.setPosition(windowSize.x / 2 + 100, windowSize.y * 2 / 3);

	gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
	gameOver.setScale(3, 3);
	gameOver.setPosition(windowSize.x / 2, windowSize.y /8);

	/* Copied from MainMenu*/
	font.loadFromFile("fonts/flappyBird.ttf");
	highScore.setFont(font);
	highScore.setString("0");
	highScore.setCharacterSize(100);
	highScore.setFillColor(sf::Color::Yellow);
	highScore.setOutlineColor(sf::Color::Black);
	highScore.setOutlineThickness(1.5f);

	PausedText.setFont(font);
	PausedText.setString("Paused");
	PausedText.setCharacterSize(200);
	PausedText.setFillColor(sf::Color::Yellow);
	PausedText.setOutlineColor(sf::Color::Black);
	PausedText.setOutlineThickness(1.5f);
	PausedText.setOrigin(PausedText.getGlobalBounds().width / 2, PausedText.getGlobalBounds().height / 2);
	PausedText.setPosition(windowSize.x / 2, windowSize.y * 1 / 9);

	highScore.setOrigin(highScore.getGlobalBounds().width / 2, highScore.getGlobalBounds().height / 2);
	highScore.setPosition(windowSize.x / 2, windowSize.y * 4 / 9);
	highScoreLabel = highScore;
	highScoreLabel.setCharacterSize(60);
	highScoreLabel.setString("highscore");
	highScoreLabel.setPosition(windowSize.x / 2, windowSize.y * 3.3 / 9);
	highScoreLabel.setOrigin(highScoreLabel.getGlobalBounds().width / 2, highScoreLabel.getGlobalBounds().height / 2);
}

Pause::PressedButton Pause::isClicked(sf::Vector2i mousePos) {
	if (state != State::DiePaused)
	if (btnPlay.getGlobalBounds().contains(mousePos.x, mousePos.y))
		return PressedButton::btnResumePressed;
	if (btnMenu.getGlobalBounds().contains(mousePos.x, mousePos.y))
		return PressedButton::btnMenuPressed;
	if (btnPause.getGlobalBounds().contains(mousePos.x, mousePos.y))
		return PressedButton::btnPausePressed;
	if (btnStart.getGlobalBounds().contains(mousePos.x, mousePos.y))
		return PressedButton::btnStartNewPressed;
}

void Pause::setState(State _state) {
	state = _state;
}

void Pause::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	
	switch (state) {
		case State::InMenu: {
			break;
		};
		case State::InGame:{
			target.draw(btnPause, states);
			break;
		};
		case State::Paused: {
			target.draw(PausedText, states);
			target.draw(btnMenu, states);
			target.draw(btnPlay, states);
			break;
		};
		case State::DiePaused: {
			target.draw(gameOver, states);
			target.draw(btnStart, states);
			target.draw(btnMenu, states);
			target.draw(highScore, states);
			target.draw(highScoreLabel,states);
			break;
		};
	}
}


Pause::~Pause(){

}
