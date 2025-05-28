#include "ButtonRetry.hpp"

ButtonRetry::ButtonRetry(/*sf::Vector2f position*/):
    UIButton(/*position*/)
{
    m_buttonStatus = {
        sf::IntRect(sf::Vector2i(32, 32), sf::Vector2i(32, 32)),
        sf::IntRect(sf::Vector2i(64, 32), sf::Vector2i(32, 32))
    };
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
}

void ButtonRetry::onClick()
{
}
