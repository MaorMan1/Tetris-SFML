#include "DisplayWindow.hpp"
#include "ResourcesManager.hpp"

DisplayWindow::DisplayWindow(sf::Vector2f position, sf::Vector2f size, const std::string& title, DisplaysOptions option)
    : m_position(position), 
    m_size(size),
    m_dispPivot(sf::Vector2i(5,3)), // Adjusted default
    m_title(title), 
    m_option(option),
    m_titleText(ResourcesManager::get().getFont("main")), 
    m_valueText(ResourcesManager::get().getFont("main"))
{
    m_background.setSize(size);
    m_background.setPosition(position);
    m_background.setFillColor(sf::Color(30, 30, 30, 200));
    m_background.setOutlineColor(sf::Color::White);
    m_background.setOutlineThickness(2.f);

    m_titleText.setString(title);
    m_titleText.setCharacterSize(36);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setPosition(sf::Vector2f(position.x + 8.f, position.y + 4.f));

    m_valueText.setCharacterSize(36);
    m_valueText.setFillColor(sf::Color::Cyan);
    //m_valueText.setPosition(sf::Vector2f(position.x + 8.f, position.y + 28.f));
}

void DisplayWindow::setValue(const std::string& value) {
    m_value = value;
    m_valueText.setString(m_value);

    // Center the value text inside the display box
    sf::FloatRect textBounds = m_valueText.getLocalBounds();
    m_valueText.setOrigin(
        sf::Vector2f(
        textBounds.position.x + textBounds.size.x / 2.f,
        textBounds.position.y + textBounds.size.y / 2.f)
    );

    // Center position = display top-left + half size
    sf::Vector2f center = m_position + m_size / 2.f;
    m_valueText.setPosition(center);
}

void DisplayWindow::setTitle(const std::string& title) {
    m_title = title;
    m_titleText.setString(title);
}

void DisplayWindow::draw(sf::RenderWindow& window, const int alpha, const CubePattern* piece, const float blockSize) const {
    window.draw(withAlpha(m_background, alpha));
    window.draw(withAlpha(m_titleText, alpha));
    switch (m_option) {
    case DisplaysOptions::Score:
        window.draw(withAlpha(m_valueText, alpha));
        break;
    case DisplaysOptions::NextPattern:
        if(piece) 
            piece->drawDisplayPattern(window, blockSize, *this, alpha);
        break;
    }
}

sf::Vector2f DisplayWindow::getPosition() const
{
    return m_position;
}

sf::Vector2f DisplayWindow::getSize() const
{
    return m_size;
}

sf::Vector2i DisplayWindow::getDispPivot() const {
    return m_dispPivot;
}

// If needed later
sf::Vector2f DisplayWindow::getCenter() const {
    return m_position + m_size / 2.f;
}
