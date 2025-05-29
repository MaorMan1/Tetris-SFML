#include "UIButton.hpp"

UIButton::UIButton():
	m_sprite(ResourcesManager::get().getTexture("buttons")),
	m_currentStatus(ButtonStatus::Normal)
	{}

void UIButton::draw(sf::RenderWindow& window, const int alpha) const
{
	auto sprite = m_sprite;
	auto c = sprite.getColor();
	c.a = alpha;
	sprite.setColor(c);
	window.draw(sprite);
}

void UIButton::update()
{
	m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(m_currentStatus)]);
	// ??

	/*if (!isClicked(mousePos))
		return;*/

}

bool UIButton::isClicked(const sf::Vector2f& mousePos) const
{
	// ??
	return true;
}

void UIButton::setHeldClicked(const bool isClicked)
{
	m_heldClick = isClicked;
	m_currentStatus = (isClicked)? ButtonStatus::Clicked: ButtonStatus::Normal;
}

bool UIButton::isHeldClick() const
{
	return m_heldClick;
}

bool UIButton::isHovered(const sf::Vector2f& mousePos)
{
	return m_sprite.getGlobalBounds().contains(mousePos);
}

void UIButton::setPositionAndScale(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	float scaleX = size.x / m_sprite.getTextureRect().size.x;
	float scaleY = size.y / m_sprite.getTextureRect().size.y;

	m_sprite.setScale(sf::Vector2f(scaleX, scaleY));
	m_sprite.setPosition(pos);
}
