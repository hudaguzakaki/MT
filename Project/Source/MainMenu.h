#pragma once
#include <SFML/Graphics.hpp>

class MainMenu : public sf::Drawable
{
public:
	MainMenu(sf::Vector2u windowSize, int score);
	~MainMenu();
	bool isClicked(sf::Vector2i mousePos);
	bool CheckScore(int tryScore) {
		bool returnValue = false;
		if (tryScore > highScoreNum) {
			highScoreNum = tryScore;
			highScore.setString(std::to_string(highScoreNum));
			highScore.setOrigin(highScore.getGlobalBounds().width / 2, highScore.getGlobalBounds().height / 2);
			return returnValue = true;
		}
		return returnValue;
	}
	int getHighScore() {
		return highScoreNum;
	}

private:
	int highScoreNum;
	sf::Sprite btnPlay;
	sf::Texture btnPlayTexture;
	sf::Sprite Logo;
	sf::Texture LogoTexture;

	sf::Text highScore;
	sf::Text highScoreLabel;
	sf::Font font;



	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

