#include "FireTrailAnimation.hpp"

FireTrailAnimation::FireTrailAnimation()
    : m_texture(&ResourcesManager::get().getTexture("fire_trail")),
    m_sprite(*m_texture),
    m_frameTime(sf::seconds(0.09f))
{
    // Load 5 frames from the sprite sheet (each 55x62 pixels)
    m_frames = {
        sf::IntRect(sf::Vector2i(27, 22), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(157, 22), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(27, 130), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(157, 130), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(27, 259), sf::Vector2i(55, 62))
    };
}

void FireTrailAnimation::start(const sf::Vector2f& position) {
    if (!m_active) {
        m_currentFrame = 0;
        m_loopMode = false;
        m_elapsed = sf::Time::Zero;
    }
    m_active = true;
    m_worldPosition = position;
    updateSpriteFrame();  // Set frame and origin
}

void FireTrailAnimation::stop() {
    m_active = false;
}

void FireTrailAnimation::update(sf::Time dt) {
    if (!m_active) return;

    m_elapsed += dt;
    if (m_elapsed >= m_frameTime) {
        m_elapsed -= m_frameTime;

        // Animation progression logic
        if (!m_loopMode) {
            m_currentFrame++;
            if (m_currentFrame >= 4) {
                m_currentFrame = 4;
                m_loopMode = true;
            }
        }
        else {
            m_currentFrame = (m_currentFrame == 3) ? 4 : 3;
        }

        updateSpriteFrame();
    }
}

void FireTrailAnimation::draw(sf::RenderWindow& window, float blockSize, sf::Vector2f boardOffset) {
    if (!m_active) return;

    // Correct sprite origin and scaling to center it under the falling piece
    m_sprite.setPosition(sf::Vector2f(m_worldPosition.x + blockSize * 0.5f,
        m_worldPosition.y - m_sprite.getGlobalBounds().size.y + blockSize));

    float scaleFactor = blockSize / 16.f;  // Adjust scale to fit game block size
    m_sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));

    window.draw(m_sprite);
}

bool FireTrailAnimation::isFinished() const {
    return !m_active;
}

void FireTrailAnimation::updateSpriteFrame() {
    const auto& rect = m_frames[m_currentFrame];
    m_sprite.setTextureRect(rect);
    m_sprite.setOrigin(sf::Vector2f(static_cast<float>(rect.size.x) / 2.f,
        static_cast<float>(rect.size.y) / 2.f));
}
