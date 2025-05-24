#ifndef TETRIS_UIBUTTON_HPP
#define TETRIS_UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"

class UIButton {
protected:
    sf::Sprite m_sprite;
    sf::FloatRect m_bounds;
    bool m_hovered = false;

public:
    UIButton(const sf::Texture& texture, sf::Vector2f position);
    virtual void draw(sf::RenderWindow& window) const;
    virtual void update(const sf::Vector2f& mousePos);
    virtual bool isClicked(const sf::Vector2f& mousePos) const;
    virtual void onClick() = 0; // Pure virtual
    virtual ~UIButton() = default;
};

#endif
