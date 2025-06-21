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
#include "ButtonMute.hpp"

// Forward declarations
class CubePattern;
class DisplayWindow;

// UI bar on the right: handles score, next piece, and buttons (pause, retry, etc.)
class UIBar {
public:
	// Constructor
	UIBar(sf::Vector2u windowSize, const float blockSize, const sf::Vector2f boardOffset);
	
	float getBlockSize() const;
	sf::Vector2f getUIBarOffset();

	void updateScore(int score);
	void updateNextPiece(CubePattern* nextPiece);

	void draw(sf::RenderWindow& window, const int alpha = 255);
	void update();	// Update all button animations/states
	void resetButtons();	// Reset click/hover states

	void mouseButtonClick(const sf::Vector2f& mousePos);	// On click down
	Button mouseButtonHandle();	// On click release

private:
	std::vector<DisplayWindow> m_displays;	
	std::vector<std::unique_ptr<UIButton>> m_buttons;

	sf::Sprite m_blockSprite; 
	float m_blockSize;
	sf::Vector2f m_UIBarOffset;

	CubePattern* m_nextPiece = nullptr; // Non-owning the pointer! Only used for preview

	void drawBackground(sf::RenderWindow& window, int alpha);
	void positionButtons(sf::Vector2u windowSize, const float space);
};

#endif