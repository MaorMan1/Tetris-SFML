#ifndef TETRIS_GRAVITYTIMER_HPP
#define TETRIS_GRAVITYTIMER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class GravityTimer
 * @brief Manages time-based piece falling logic for the Tetris board.
 *
 * Uses an internal SFML clock to determine when the active piece
 * should fall according to the current gravity delay.
 * Allows dynamic speed-up over time and provides delay information.
 */
class GravityTimer {
public:
    GravityTimer() = default;

    /**
     * @brief Start or restart the gravity timer with a given delay in seconds.
     */
    void start(float seconds);

    /**
     * @brief Returns true if enough time has passed to allow a fall step.
     */
    bool shouldFall() const;

    /**
     * @brief Resets the internal clock to wait for the next fall interval.
     */
    void reset();

    /**
     * @brief Decreases the fall delay by a factor (default = 0.95), with clamping.
     */
    void speedUp(float factor = 0.95f);

    /**
     * @brief Gets the current delay between gravity updates.
     */
    float getDelay() const;

private:
    sf::Clock m_clock;  ///< Tracks elapsed time since last fall
    float m_delay = 1.0f; ///< Delay threshold in seconds
};


#endif