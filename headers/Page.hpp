#ifndef TETRIS_PAGE_HPP
#define TETRIS_PAGE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"

class Page {
public:
    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~Page() = default;
};

#endif
