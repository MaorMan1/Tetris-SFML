#ifndef TETRIS_UIBUTTON_HPP
#define TETRIS_UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"

class UIButton {
protected:
    sf::Sprite m_sprite;
    //sf::FloatRect m_bounds;
    bool m_hovered = false;
    std::vector<sf::IntRect> m_buttonStatus;


public:
    UIButton();
    virtual void draw(sf::RenderWindow& window, const int alpha = 255) const;
    virtual void update(const sf::Vector2f& mousePos);
    virtual bool isClicked(const sf::Vector2f& mousePos) const;
    virtual void onClick() = 0; // Pure virtual
    virtual ~UIButton() = default;
    void setPositionAndScale(const sf::Vector2f& pos, const sf::Vector2f& size);
};

#endif
