#include "LineClearAnimation.hpp"

LineClearAnimation::LineClearAnimation()
    : m_frameDuration(sf::seconds(0.5f)), // Default speed (adjusted dynamically later)
    m_elapsed(sf::Time::Zero),
    m_currentFrame(0),
    m_explosionTexture(&ResourcesManager::get().getTexture("block_explosion")),
    m_beforeExplosionPlayed(false)
{
    // Define frames manually based on the explosion sprite sheet
    m_frames = {
        sf::IntRect(sf::Vector2i(35, 35), sf::Vector2i(62, 62)),
        sf::IntRect(sf::Vector2i(155, 31), sf::Vector2i(74, 70)),
        sf::IntRect(sf::Vector2i(275, 23), sf::Vector2i(94, 84)),
        sf::IntRect(sf::Vector2i(0, 147), sf::Vector2i(128, 100)),
        sf::IntRect(sf::Vector2i(128, 147), sf::Vector2i(128, 100)),
        sf::IntRect(sf::Vector2i(256, 147), sf::Vector2i(128, 100)),
        sf::IntRect(sf::Vector2i(0, 282), sf::Vector2i(128, 100))
    };
}

void LineClearAnimation::start(const std::set<int>& rowsToClear)
{
    m_blocks.clear();
    m_activateColumn = 0;

    // Initialize all cells in the rows as ready for explosion
    for (int row : rowsToClear) {
        for (int col = 0; col < WIDTH; ++col) {
            m_blocks[{row, col}] = ExplosionBlock{ 0, false }; // Frame 0, not active yet
        }
    }

    m_elapsed = sf::Time::Zero;
}

void LineClearAnimation::update(sf::Time dt)
{
    if (m_blocks.empty())
        return; // Nothing to animate

    m_elapsed += dt;

    // Dynamically reduce the activation delay: create an accelerating effect
    float baseDuration = 0.2f;
    float accelerationFactor = 0.85f;
    m_frameDuration = sf::seconds(baseDuration * std::pow(accelerationFactor, m_activateColumn));

    if (m_elapsed >= m_frameDuration) {
        m_elapsed -= m_frameDuration;

        if (m_activateColumn < WIDTH) {
            if (!m_beforeExplosionPlayed) {
                m_beforeExplosionPlayed = true;
                ResourcesManager::get().getSound("before_explosion").play();
            }
            for (auto& [pos, block] : m_blocks) {
                if (pos.second == m_activateColumn && !block.active) {
                    block.active = true;
                }
            }
            m_activateColumn++; // Next column on next frame
        }
        else {
            if (m_beforeExplosionPlayed) {
                m_beforeExplosionPlayed = false;
                ResourcesManager::get().getSound("before_explosion").stop();
                ResourcesManager::get().getSound("explosion_sound").play();
            }
            // After all columns activated: Progress animation frames
            for (auto& [_, block] : m_blocks) {
                if (block.active) {
                    block.frame++;
                }
            }

            // Check if every block finished its animation
            bool done = true;
            for (auto& [_, block] : m_blocks) {
                if (block.frame < static_cast<int>(m_frames.size())) {
                    done = false;
                    break;
                }
            }
            if (done) {
                m_blocks.clear(); // All animations finished
            }
        }
    }
}


void LineClearAnimation::draw(sf::RenderWindow& window, float blockSize, sf::Vector2f boardOffset)
{
    if (m_blocks.empty())
        return;

    sf::Sprite sprite(*m_explosionTexture);

    for (const auto& [pos, block] : m_blocks) {
        if (!block.active || block.frame >= static_cast<int>(m_frames.size()))
            continue;

        const sf::IntRect& frameRect = m_frames[block.frame];
        sprite.setTextureRect(frameRect);

        // Scale explosion frame to fit inside a block size
        float scaleX = blockSize / static_cast<float>(frameRect.size.x);
        float scaleY = blockSize / static_cast<float>(frameRect.size.y);

        sprite.setScale(sf::Vector2f(scaleX, scaleY));

        sf::Vector2f cellPos;
        cellPos.x = boardOffset.x + pos.second * blockSize;
        cellPos.y = boardOffset.y + pos.first * blockSize;

        // Center the explosion effect in the cell
        sf::Vector2f correction;
        correction.x = (blockSize - frameRect.size.x * scaleX) / 2.f;
        correction.y = (blockSize - frameRect.size.y * scaleY) / 2.f;

        sprite.setPosition(cellPos + correction);

        window.draw(sprite);
    }
}

bool LineClearAnimation::isFinished() const
{
    return m_blocks.empty();
}
