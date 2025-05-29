#ifndef TETRIS_UIBUTTON_HPP
#define TETRIS_UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "Globals.hpp"

class UIButton {
protected:
    sf::Sprite m_sprite;
    bool m_onHoldToHandle = false;
    bool m_heldClick = false;
    std::vector<sf::IntRect> m_buttonStatus;
    ButtonStatus m_currentStatus;

public:
    UIButton();
    virtual void draw(sf::RenderWindow& window, const int alpha = 255) const;
    virtual void update();
    virtual bool isClicked(const sf::Vector2f& mousePos) const;
    virtual Button onClick() = 0; // Pure virtual
    virtual void reset() = 0; // Pure virtual
    virtual ~UIButton() = default;
    void setHeldClicked(const bool isClicked);
    bool isHeldClick() const;
    bool isHovered(const sf::Vector2f& mousePos);
    void setPositionAndScale(const sf::Vector2f& pos, const sf::Vector2f& size);
};

#endif
