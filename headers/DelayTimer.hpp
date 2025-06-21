#ifndef TETRIS_DELAY_TIMER_HPP
#define TETRIS_DELAY_TIMER_HPP

#include <SFML/System.hpp>

/*
 * DelayTimer provides a simple timer utility using SFML's clock.
 * Can be used for delayed actions like transitions, animations, etc.
 */
class DelayTimer {
public:
    DelayTimer() = default;

    // Start the timer with a duration in seconds
    void start(float seconds);

    // Returns true if the timer is active and time has passed
    bool isDone() const;

    // Returns true if the timer is currently active
    bool isActive() const;

    // Manually resets the timer (stops it)
    void reset();

    // Returns elapsed time since start
    sf::Time getElapsed() const;

    // Returns the full duration set for this timer
    sf::Time getDuration() const;

private:
    sf::Clock m_clock;
    sf::Time m_duration;
    bool m_active = false;
};


#endif