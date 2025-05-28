#include "ButtonPause.hpp"

ButtonPause::ButtonPause()
{
    m_pauseSprites = {
        sf::IntRect(sf::Vector2i(4*32,8*32), sf::Vector2i(32, 32)),
        sf::IntRect(sf::Vector2i(5*32,8*32), sf::Vector2i(32, 32))
    };
    m_playSprites = {
        sf::IntRect(sf::Vector2i(4*32,3*32), sf::Vector2i(32, 32)),
        sf::IntRect(sf::Vector2i(5*32,3*32), sf::Vector2i(32, 32))
    };
    // Default while playing to see pause button
    m_buttonStatus = m_pauseSprites;

    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
}

void ButtonPause::onClick()
{
}
