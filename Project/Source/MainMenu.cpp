#include "MainMenu.h"


MainMenu::MainMenu(sf::Vector2u windowSize,int score) {
	btnPlayTexture.loadFromFile("images/play.png");
	btnPlay.setTexture(btnPlayTexture);
	btnPlay.setOrigin(btnPlay.getGlobalBounds().width / 2, btnPlay.getGlobalBounds().height / 2);
	btnPlay.setScale(0.8, 0.8);
	btnPlay.setPosition(windowSize.x / 2, windowSize.y * 6.5 / 9);

	LogoTexture.loadFromFile("images/Logo.png");
	Logo.setTexture(LogoTexture);
	Logo.setOrigin(Logo.getGlobalBounds().width / 2, Logo.getGlobalBounds().height / 2);
	Logo.setScale(4.0f, 4.0f);
	Logo.setPosition(windowSize.x / 2, windowSize.y * 2 / 9);

	font.loadFromFile("fonts/flappyBird.ttf");
	highScore.setFont(font);
	highScore.setString(std::to_string(highScoreNum));
	highScore.setCharacterSize(100);
	highScore.setFillColor(sf::Color::Yellow);
	highScore.setOutlineColor(sf::Color::Black);
	highScore.setOutlineThickness(1.5f);

	highScore.setOrigin(highScore.getGlobalBounds().width / 2, highScore.getGlobalBounds().height / 2);
	highScore.setPosition(windowSize.x / 2, windowSize.y * 4 / 9);
	highScoreLabel = highScore;
	highScoreLabel.setCharacterSize(60);
	highScoreLabel.setString("highscore");
	highScoreLabel.setPosition(windowSize.x / 2, windowSize.y * 3.3 / 9);
	highScoreLabel.setOrigin(highScoreLabel.getGlobalBounds().width / 2, highScoreLabel.getGlobalBounds().height / 2);
}

bool MainMenu::isClicked(sf::Vector2i mousePos) {
	if (btnPlay.getGlobalBounds().contains(mousePos.x,mousePos.y))
		return true;
	else return false;
}



void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(highScoreLabel);
	target.draw(btnPlay, states);
	target.draw(highScore, states);
	target.draw(Logo, states);
}

MainMenu::~MainMenu() {

}
