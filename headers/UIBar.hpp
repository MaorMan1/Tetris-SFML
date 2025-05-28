#ifndef TETRIS_UIBAR_HPP
#define TETRIS_UIBAR_HPP	

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include "ResourcesManager.hpp"
#include "DisplayWindow.hpp"
#include "CubePattern.hpp"
#include "ButtonRetry.hpp"
#include "ButtonPause.hpp"
#include "ButtonBackToMenu.hpp"

// Forward declarations
class CubePattern;
class DisplayWindow;

class UIBar {
public:
	UIBar(sf::Vector2u windowSize, const float blockSize, const sf::Vector2f boardOffset);
	
	float getBlockSize() const;
	sf::Vector2f getUIBarOffset();
	//check
	void updateScore(int score);
	void updateNextPiece(CubePattern* nextPiece);
	void draw(sf::RenderWindow& window, const int alpha = 255);

private:
	//check
	std::vector<DisplayWindow> m_displays;
	std::vector<std::unique_ptr<UIButton>> m_buttons;

	sf::Sprite m_blockSprite; 
	float m_blockSize;
	sf::Vector2f m_UIBarOffset;

	CubePattern* m_nextPiece = nullptr; // check(Pointer only (not owning))

	void drawBackground(sf::RenderWindow& window, int alpha);
	void positionButtons(sf::Vector2u windowSize, const float space);
};

#endif