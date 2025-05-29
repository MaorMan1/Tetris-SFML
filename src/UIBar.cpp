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

	m_buttons.emplace_back(std::make_unique<ButtonPause>());
	m_buttons.emplace_back(std::make_unique<ButtonBackToMenu>());
	m_buttons.emplace_back(std::make_unique<ButtonRetry>());

	positionButtons(windowSize, space);
}

void UIBar::positionButtons(sf::Vector2u windowSize, const float space)
{
	if (m_buttons.empty()) return;

	sf::Vector2f buttonSize(2 * m_blockSize, 2 * m_blockSize);
	size_t numButtons = m_buttons.size();

	float availableWidth = windowSize.x - m_UIBarOffset.x;
	float totalButtonsWidth = numButtons * buttonSize.x;
	float totalSpacing = availableWidth - totalButtonsWidth;
	float buttonSpacing = totalSpacing / (numButtons + 1);

	float yPos = windowSize.y - buttonSize.y;
	float xPos = m_UIBarOffset.x + buttonSpacing;

	for (auto& btn : m_buttons) {
		btn->setPositionAndScale(sf::Vector2f(xPos, yPos - space), buttonSize);
		xPos += buttonSize.x + buttonSpacing;
	}
}

float UIBar::getBlockSize() const
{
	return m_blockSize;
}

sf::Vector2f UIBar::getUIBarOffset()
{
	return m_UIBarOffset;
}

void UIBar::update() {
	for (const auto& btn : m_buttons)
		btn->update();
}

void UIBar::resetButtons()
{
	for (const auto& btn : m_buttons)
		btn->reset();
}

void UIBar::draw(sf::RenderWindow& window, const int alpha)
{
	drawBackground(window, alpha);
	for (const auto& dw : m_displays) {
		dw.draw(window, alpha, m_nextPiece, m_blockSize);
	}
	for (const auto& btn : m_buttons) {
		btn->draw(window, alpha);
	}
}

// After found left button click 
void UIBar::mouseButtonClick(const sf::Vector2f& mousePos)
{
	for (const auto& btn : m_buttons) {
		if (!btn->isHeldClick() && btn->isHovered(mousePos)) {
			btn->setHeldClicked(true);
		}
	}
}

// After found left button released 
Button UIBar::mouseButtonHandle()
{
	for (const auto& btn : m_buttons) {
		if (btn->isHeldClick()) {
			btn->setHeldClicked(false);
			return btn->onClick();
		}
	}
	return Button::None;
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

