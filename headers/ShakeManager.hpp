#ifndef TETRIS_SHAKEMANAGER_HPP
#define TETRIS_SHAKEMANAGER_HPP

#include <SFML/Graphics.hpp>

class ShakeManager {
public:
    void start(float duration, float strength);
    void update(sf::Time dt);
    sf::Vector2f getShakeOffset() const;
    bool isShaking() const;

private:
    float m_duration = 0.f;
    float m_strength = 0.f;
    float m_elapsed = 0.f;
    sf::Vector2f m_currentOffset = { 0.f, 0.f };
};

#endif
