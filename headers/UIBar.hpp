#ifndef TETRIS_UIBAR_HPP
#define TETRIS_UIBAR_HPP	

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include "ResourcesManager.hpp"

class UIBar {
public:
	UIBar(sf::Vector2u windowSize, const float blockSize, const sf::Vector2f boardOffset);
	float getBlockSize() const;
	sf::Vector2f getUIBarOffset();
	void draw(sf::RenderWindow& window, const int alpha = 255);

private:
	sf::Sprite m_blockSprite; 
	float m_blockSize;
	sf::Vector2f m_UIBarOffset;
};

#endif