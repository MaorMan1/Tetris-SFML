#include "ButtonMute.hpp"

ButtonMute::ButtonMute():
    m_muted(false)
{
    m_muteSprites = {
        sf::IntRect(sf::Vector2i(1 * 32,0 * 32), sf::Vector2i(32, 32)), // Normal mute
        sf::IntRect(sf::Vector2i(2 * 32,0 * 32), sf::Vector2i(32, 32))  // Clicked mute
    };
    m_unmuteSprites = {
        sf::IntRect(sf::Vector2i(7 * 32,7 * 32), sf::Vector2i(32, 32)), // Normal unmute
        sf::IntRect(sf::Vector2i(8 * 32,7 * 32), sf::Vector2i(32, 32))  // Clicked unmute
    };
    // Default while playing to see unmuted button
    m_buttonStatus = m_unmuteSprites;

    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
}

Button ButtonMute::onClick()
{
    // Toggle state
    m_buttonStatus = (m_muted) ? m_unmuteSprites:  m_muteSprites;    // Change Mute/Unmute sprites
    m_muted = !m_muted;

    return m_muted ? Button::Mute : Button::Unmute;
}

void ButtonMute::reset()
{
    m_buttonStatus = m_unmuteSprites;
    m_currentStatus = ButtonStatus::Normal;
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
    m_muted = false;
}
