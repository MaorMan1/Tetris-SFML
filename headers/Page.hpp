#ifndef TETRIS_PAGE_HPP
#define TETRIS_PAGE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"

// Base class for all pages (Menu, About, Gameplay, LeaderBoard, etc.)
class Page {
protected:
    bool m_backToMenu = false; // Flag to signal returning to menu

public:
    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Page() = default;

    bool wantsToReturn() const { return m_backToMenu; }
};

#endif
