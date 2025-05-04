#ifndef TETRIS_BASE_ANIMATION_HPP
#define TETRIS_BASE_ANIMATION_HPP

#include <SFML/Graphics.hpp>

class BaseAnimation {
public:
    virtual ~BaseAnimation() = default;

    // Update animation state
    virtual void update(sf::Time dt) = 0;

    // Draw current frame
    virtual void draw(sf::RenderWindow& window, float blockSize, sf::Vector2f boardOffset) = 0;

    // Check if animation is done
    virtual bool isFinished() const = 0;
};

#endif
