#ifndef TETRIS_DELAY_TIMER_HPP
#define TETRIS_DELAY_TIMER_HPP

#include <SFML/System.hpp>

class DelayTimer {
public:
    DelayTimer() = default;

    void start(float seconds);
    bool isDone() const;
    bool isActive() const;
    void reset();
    sf::Time getElapsed() const;
    sf::Time getDuration() const;

private:
    sf::Clock m_clock;
    sf::Time m_duration;
    bool m_active = false;
};

#endif