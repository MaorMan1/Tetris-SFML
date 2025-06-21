#include "ButtonRetry.hpp"

ButtonRetry::ButtonRetry():
    UIButton()
{
    m_buttonStatus = {
        sf::IntRect(sf::Vector2i(32, 32), sf::Vector2i(32, 32)), // Normal state   
        sf::IntRect(sf::Vector2i(64, 32), sf::Vector2i(32, 32))  // Clicked state
    };
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
}

Button ButtonRetry::onClick()
{
    // Logic handled externally
    return Button::Retry;
}

void ButtonRetry::reset()
{
    m_currentStatus = ButtonStatus::Normal;
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(m_currentStatus)]);
}
