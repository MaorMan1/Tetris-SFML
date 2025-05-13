#include "UIBar.hpp"

UIBar::UIBar(sf::Vector2u windowSize, const float blockSize, const sf::Vector2f boardOffset):
	m_blockSize(blockSize),
	m_UIBarOffset(sf::Vector2f(blockSize*WIDTH + boardOffset.x, boardOffset.y)),
	m_blockSprite(ResourcesManager::get().getTexture("ui_bar_bg"))
{
	m_blockSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(128, 128)));
	float scaleX = blockSize / static_cast<float>(m_blockSprite.getGlobalBounds().size.x); 
	float scaleY = blockSize / static_cast<float>(m_blockSprite.getGlobalBounds().size.y);
	m_blockSprite.setScale(sf::Vector2f(scaleX, scaleY));
}

float UIBar::getBlockSize() const
{
	return m_blockSize;
}

sf::Vector2f UIBar::getUIBarOffset()
{
	return m_UIBarOffset;
}

void UIBar::draw(sf::RenderWindow& window, const int alpha)
{
	// Set oppacity of UI Bar by given alpha (255 by default)
	auto c = m_blockSprite.getColor();
	c.a = alpha;
	m_blockSprite.setColor(c);

	// Calculate blocks number from UI Bar offset till the end of the window size and draw.
	int cols = (window.getSize().x - static_cast<int>(m_UIBarOffset.x)) / m_blockSize;
	int rows = (window.getSize().y - static_cast<int>(m_UIBarOffset.y)) / m_blockSize;

	for (int y = 0; y <= rows; ++y) {
		for (int x = 0; x <= cols; ++x) {
			sf::Vector2f pos;
			pos.x = m_UIBarOffset.x + x * m_blockSize;
			pos.y = m_UIBarOffset.y + y * m_blockSize;
			m_blockSprite.setPosition(pos);

			window.draw(m_blockSprite);
		}
	}
}
