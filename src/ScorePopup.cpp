#include "ScorePopup.hpp"

ScorePopup::ScorePopup(const sf::Font& font, const sf::Vector2f& position, const std::string& text, sf::Color color)
    : m_velocity(0.f, -30.f), 
    m_lifetime(sf::seconds(0)),
    m_text(font)
{
    m_text.setString(text);
    m_text.setCharacterSize(50);
    m_text.setFillColor(color);
    m_text.setPosition(position);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(2);

    // Center the text origin
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
}

void ScorePopup::update(sf::Time dt)
{
    m_lifetime += dt;
    m_text.move(m_velocity * dt.asSeconds());

    // Fade out over time
    float fadeDuration = 2.0f; // Duration time to fade

    float alpha = 255 * (1.f - m_lifetime.asSeconds() / fadeDuration);
    if (alpha < 0.f) alpha = 0.f;
    sf::Color color = m_text.getFillColor();
    color.a = static_cast<int>(alpha);
    m_text.setFillColor(color);
}

void ScorePopup::draw(sf::RenderTarget& target) const
{
    target.draw(m_text);
}

bool ScorePopup::isFinished() const
{
    return m_lifetime.asSeconds() >= 1.0f;
}
