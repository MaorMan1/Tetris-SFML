#ifndef TETRIS_SCOREPOPUP_HPP
#define TETRIS_SCOREPOPUP_HPP

#include <SFML/Graphics.hpp>

class ScorePopup {
public:
    ScorePopup(const sf::Font& font, const sf::Vector2f& position, const std::string& text, sf::Color color = sf::Color::White);

    void update(sf::Time dt);
    void draw(sf::RenderTarget& target) const;
    bool isFinished() const;

private:
    sf::Text m_text;
    sf::Vector2f m_velocity;
    sf::Time m_lifetime;
};

#endif
