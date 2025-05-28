#include "ButtonBackToMenu.hpp"

ButtonBackToMenu::ButtonBackToMenu()
{
    m_buttonStatus = {
        sf::IntRect(sf::Vector2i(320, 0), sf::Vector2i(32, 32)),    
        sf::IntRect(sf::Vector2i(352, 0), sf::Vector2i(32, 32))
    };
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
}

void ButtonBackToMenu::onClick()
{
}
