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

	float space = 10.f;
	float displaySize = blockSize * 6.f;

	float uiBarWidth = windowSize.x - m_UIBarOffset.x;
	float centerX = m_UIBarOffset.x + (uiBarWidth - 2*displaySize) / 2.f;

	// Display 1: Score
	m_displays.emplace_back(sf::Vector2f(centerX, m_UIBarOffset.y + space),
		sf::Vector2f(2*displaySize, displaySize),
		"Score:", DisplaysOptions::Score);

	// Display 2: Next
	m_displays.emplace_back(sf::Vector2f(centerX, m_UIBarOffset.y + 2 * space + displaySize),
		sf::Vector2f(2*displaySize, displaySize),
		"Next:", DisplaysOptions::NextPattern);
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
	drawBackground(window, alpha);
	for (const auto& dw : m_displays) {
		dw.draw(window, alpha, m_nextPiece, m_blockSize);
	}


	// new check!!
	// Draw next piece into the 2nd DisplayWindow
	//	const auto& pattern = m_nextPiece->getPatternPositions();
	//	char sign = m_nextPiece->getPatternGridSign();

	//	sf::Sprite blockSprite(ResourcesManager::get().getTexture("block_sheet"));
	//	blockSprite.setTextureRect(ResourcesManager::get().getBlockTextureRect(sign));
	//	float tileSize = m_blockSize * 0.75f; // slightly smaller
	//	blockSprite.setScale(tileSize / 32.f, tileSize / 32.f);

	//	const sf::Vector2f& boxPos = m_displays[1].getPosition();
	//	const sf::Vector2f& boxSize = m_displays[1].getSize();

	//	// Center sprite drawing inside the window
	//	sf::Vector2f center = boxPos + boxSize / 2.f;

	//	int rows = static_cast<int>(pattern.size());
	//	int cols = static_cast<int>(pattern[0].size());

	//	for (int r = 0; r < rows; ++r) {
	//		for (int c = 0; c < cols; ++c) {
	//			if (pattern[r][c] != ' ')
	//			{
	//				sf::Vector2f offset((c - cols / 2.f) * tileSize, (r - rows / 2.f) * tileSize);
	//				blockSprite.setPosition(center + offset);
	//				window.draw(blockSprite);
	//			}
	//		}
	//	}
	//}
}

void UIBar::drawBackground(sf::RenderWindow& window, int alpha)
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

void UIBar::updateScore(int newScore) {
	m_displays[static_cast<int>(DisplaysOptions::Score)].setValue(std::to_string(newScore));
}

void UIBar::updateNextPiece(CubePattern* nextPiece)
{
	m_nextPiece = nextPiece;
}
