#ifndef TETRIS_SHAKEMANAGER_HPP
#define TETRIS_SHAKEMANAGER_HPP

#include <SFML/Graphics.hpp>

// Manages camera shake effects (e.g., after a line clear).
// Usage:
//  - Call start(duration, strength) to initiate a shake
//  - Call update(dt) each frame
//  - Use getShakeOffset() to apply to rendering
class ShakeManager {
public:
    void start(float duration, float strength);      // Begin shake for given time and strength
    void update(sf::Time dt);                        // Progress shake timing per frame
    sf::Vector2f getShakeOffset() const;             // Current offset to apply to drawing
    bool isShaking() const;                          // True if shake is ongoing

private:
    float m_duration = 0.f;          // Total shake time in seconds
    float m_strength = 0.f;          // Maximum shake offset magnitude
    float m_elapsed = 0.f;           // Time passed since shake started
    sf::Vector2f m_currentOffset{};  // Offset applied for current frame
};

#endif
