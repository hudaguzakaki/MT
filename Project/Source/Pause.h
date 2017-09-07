#pragma once
#include <SFML/Graphics.hpp>

class Pause : public sf::Drawable
{
public:
	enum State { Paused, DiePaused, InGame, InMenu };
	enum PressedButton { btnResumePressed, btnStartNewPressed, btnMenuPressed, btnPausePressed };
	Pause(sf::Vector2u windowSize, State _state);
	~Pause();
	PressedButton isClicked(sf::Vector2i mousePos);
	void setState(State state_);
	State state;
	void setNewHighScore(int newNum) {
		highScore.setString(std::to_string(newNum));
		highScore.setOrigin(highScore.getGlobalBounds().width / 2, highScore.getGlobalBounds().height / 2);
	}
	

private:
	int highScoreNum;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture btnPauseTexture;
	sf::Sprite btnPause;

	sf::Texture btnPlayTexture;
	sf::Sprite btnPlay;

	sf::Texture btnMenuTexture;
	sf::Sprite btnMenu;

	sf::Texture btnStartTexture;
	sf::Sprite btnStart;

	sf::Texture gameOverTexture;
	sf::Sprite gameOver;

	sf::Text highScore;
	sf::Text highScoreLabel;
	sf::Text PausedText;
	sf::Font font;

	
};

