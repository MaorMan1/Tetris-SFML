#include "ButtonBackToMenu.hpp"

ButtonBackToMenu::ButtonBackToMenu()
{
    // Define sprite regions for normal and clicked status
    m_buttonStatus = {
        sf::IntRect(sf::Vector2i(320, 0), sf::Vector2i(32, 32)),    
        sf::IntRect(sf::Vector2i(352, 0), sf::Vector2i(32, 32))
    };

    // Set initial visual
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(ButtonStatus::Normal)]);
}

Button ButtonBackToMenu::onClick()
{
    // Returning the enum Button::Home to signal main menu redirection
    return Button::Home;
}

void ButtonBackToMenu::reset()
{
    m_currentStatus = ButtonStatus::Normal;
    m_sprite.setTextureRect(m_buttonStatus[static_cast<int>(m_currentStatus)]);
}
