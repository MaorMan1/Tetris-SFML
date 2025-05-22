#ifndef TETRIS_GRAVITYTIMER_HPP
#define TETRIS_GRAVITYTIMER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

class GravityTimer {
public:
    GravityTimer() = default;
    void start(float seconds);
    bool shouldFall();
    void reset();
    void speedUp(float factor = 0.95f);
    float getDelay() const;

private:
    sf::Clock m_clock;
    float m_delay = 1.0f;
};


#endif