#ifndef TETRIS_UIBUTTON_HPP
#define TETRIS_UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "Globals.hpp"

// Base class for all UI buttons
class UIButton {
protected:
    sf::Sprite m_sprite;                          // Button sprite
    std::vector<sf::IntRect> m_buttonStatus;      // Texture rects for each visual state
    ButtonStatus m_currentStatus = ButtonStatus::Normal;

    bool m_onHoldToHandle = false;                // If the button should handle continuous holding
    bool m_heldClick = false;                     // True if the mouse is currently holding the button

public:
    UIButton();
    virtual ~UIButton() = default;

    // Rendering
    virtual void draw(sf::RenderWindow& window, int alpha = 255) const;

    // Updates current texture rect based on state
    virtual void update();

    // Check if button was clicked
    virtual bool isClicked(const sf::Vector2f& mousePos) const;

    // Called when the button is clicked – implemented by derived classes
    virtual Button onClick() = 0;

    // Reset the button's state – implemented by derived classes
    virtual void reset() = 0;

    // Mouse interactions
    void setHeldClicked(bool isClicked);
    bool isHeldClick() const;
    bool isHovered(const sf::Vector2f& mousePos);

    // Setup
    void setPositionAndScale(const sf::Vector2f& pos, const sf::Vector2f& size);
};

#endif
