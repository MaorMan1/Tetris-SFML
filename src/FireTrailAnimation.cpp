#include "FireTrailAnimation.hpp"

FireTrailAnimation::FireTrailAnimation()
    : m_texture(&ResourcesManager::get().getTexture("fire_trail")),
    m_sprite(*m_texture),
    m_frameTime(sf::seconds(1.5f))
{
    // Load 5 frames from the fire sprite sheet
    m_frames = {
        sf::IntRect(sf::Vector2i(27, 22), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(157, 22), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(27, 130), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(157, 130), sf::Vector2i(55, 62)),
        sf::IntRect(sf::Vector2i(27, 259), sf::Vector2i(55, 62))
    };

    //m_sprite.setTexture(*m_texture);
    //m_sprite.setOrigin(sf::Vector2f(0.f, 0.f)); // Centered
}

void FireTrailAnimation::start(const sf::Vector2f& position) {
    if (!m_active) {
        m_currentFrame = 0;
        m_loopMode = false;
        m_elapsed = sf::Time::Zero;
    }
    m_active = true;
    m_worldPosition = position;
    m_sprite.setTextureRect(m_frames[m_currentFrame]);
}

void FireTrailAnimation::stop() {
    m_active = false;
}

void FireTrailAnimation::update(sf::Time dt) {
    if (!m_active) return;

    m_elapsed += dt;

    if (m_elapsed >= m_frameTime) {
        m_elapsed -= m_frameTime;

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
        m_sprite.setTextureRect(m_frames[m_currentFrame]);
    }

}

void FireTrailAnimation::draw(sf::RenderWindow& window, float blockSize, sf::Vector2f boardOffset) {
    if (!m_active) return;
    //*check
    m_worldPosition.y = m_worldPosition.y - m_sprite.getGlobalBounds().size.y;
    std::cout << m_worldPosition.x << " " << m_worldPosition.y << std::endl;


    m_sprite.setPosition(m_worldPosition); // Already world-coordinated
    //m_sprite.setScale(sf::Vector2f(blockSize / 32.f, blockSize / 32.f)); // Scale to match block
    sf::Vector2f frameSize(m_frames[m_currentFrame].size.x, m_frames[m_currentFrame].size.y);
    m_sprite.setScale(sf::Vector2f(blockSize*3 / frameSize.x, blockSize*3 / frameSize.y));
    /******/
    //std::cout << "m_sprite.getPosition().x << " " << m_sprite.getPosition().y" << std::endl;

    //m_sprite.setColor(sf::Color::Red);
    /******/
    window.draw(m_sprite);
}

bool FireTrailAnimation::isFinished() const {
    return !m_active;
}