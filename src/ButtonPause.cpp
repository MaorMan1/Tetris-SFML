#include "ButtonPause.hpp"

ButtonPause::ButtonPause():
    m_paused(false)
{
    m_pauseSprites = {
        sf::IntRect(sf::Vector2i(4*32,8*32), sf::Vector2i(32, 32)), // Normal pause
        sf::IntRect(sf::Vector2i(5*32,8*32), sf::Vector2i(32, 32))  // Clicked pause
    };
    m_playSprites = {
        sf::IntRect(sf::Vector2i(4*32,3*32), sf::Vector2i(32, 32)), // Normal play
        sf::IntRect(sf::Vector2i(5*32,3*32), sf::Vector2i(32, 32))  // Clicked play
    };

    // Start unpaused (show pause icon)
    m_buttonStatus = m_pauseSprites;
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
}

Button ButtonPause::onClick()
{
    m_buttonStatus = (m_paused) ? m_pauseSprites: m_playSprites;    // Change Play/Pause sprites
    m_paused = !m_paused;

    return m_paused ? Button::Pause : Button::Play;
}

void ButtonPause::reset()
{
    m_buttonStatus = m_pauseSprites;
    m_currentStatus = ButtonStatus::Normal;
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
    m_paused = false;
}
