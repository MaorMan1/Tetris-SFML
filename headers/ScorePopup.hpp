#ifndef TETRIS_SCOREPOPUP_HPP
#define TETRIS_SCOREPOPUP_HPP

#include <SFML/Graphics.hpp>

/**
 * @brief Represents a floating score popup (e.g. "+100") that moves and fades out.
 */
class ScorePopup {
public:
    /**
     * @param font Font used for the popup text
     * @param position Starting screen position of the popup
     * @param text Text to display (e.g. "+100")
     * @param color Text color (default: white)
     */
    ScorePopup(const sf::Font& font, const sf::Vector2f& position, const std::string& text, sf::Color color = sf::Color::White);

    /**
     * @brief Updates the popup’s animation state (position and transparency).
     * @param dt Time since last frame
     */
    void update(sf::Time dt);

    /**
     * @brief Draws the popup to the given render target.
     * @param target Render window or texture
     */
    void draw(sf::RenderTarget& target) const;

    /**
     * @brief Returns true if the popup animation is finished.
     */
    bool isFinished() const;

private:
    sf::Text m_text;            ///< The floating text
    sf::Vector2f m_velocity;    ///< Direction and speed of movement
    sf::Time m_lifetime;        ///< Elapsed time since creation
    
    float m_totalLifetime; ///< Total visible time before disappearing
};

#endif
