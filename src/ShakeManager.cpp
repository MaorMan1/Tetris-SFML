#include "ShakeManager.hpp"
#include <random>

void ShakeManager::start(float duration, float strength) {
    m_duration = duration;
    m_strength = strength;
    m_elapsed = 0.f;
}

void ShakeManager::update(sf::Time dt) {
    if (m_elapsed < m_duration) {
        m_elapsed += dt.asSeconds();

        // Random small offset every frame
        static std::default_random_engine engine{ std::random_device{}() };
        static std::uniform_real_distribution<float> dist(-1.f, 1.f);

        m_currentOffset.x = dist(engine) * m_strength;
        m_currentOffset.y = dist(engine) * m_strength;
    }
    else {
        m_currentOffset = { 0.f, 0.f };
    }
}

sf::Vector2f ShakeManager::getShakeOffset() const {
    return m_currentOffset;
}

bool ShakeManager::isShaking() const {
    return m_elapsed < m_duration;
}
