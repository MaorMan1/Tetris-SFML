#include "LeaderboardPage.hpp"
#include "ResourcesManager.hpp"
#include "LeaderboardUtils.hpp"

LeaderboardPage::LeaderboardPage(sf::RenderWindow& window) :
    m_font(ResourcesManager::get().getFont("main")),
    m_bgSprite(ResourcesManager::get().getTexture("menu_bg_pic")),  // TODO change it
    m_hoverBack(false)
{
    sf::Vector2f scale = {
        static_cast<float>(window.getSize().x) / m_bgSprite.getTexture().getSize().x,
        static_cast<float>(window.getSize().y) / m_bgSprite.getTexture().getSize().y
    };
    m_bgSprite.setScale(scale);

    loadScores();

    // Title
    sf::Text title(m_font);
    title.setString("Top 5 Scores:");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Cyan);
    title.setOutlineThickness(2);
    title.setOutlineColor(sf::Color::Blue);
    auto bounds = title.getLocalBounds();
    title.setPosition(sf::Vector2f((window.getSize().x - bounds.size.x) / 2.f, 50.f));

    m_mainTexts.push_back(title);

    // Back button
    sf::Text back(m_font);
    back.setString("<< Back to Menu");
    back.setCharacterSize(30);
    back.setFillColor(sf::Color::White);
    back.setOutlineThickness(2);
    back.setOutlineColor(sf::Color::Black);
    back.setPosition(sf::Vector2f(15, 15));
    m_mainTexts.push_back(back);    

    updateScoresToTexts();
}

void LeaderboardPage::loadScores() {
    loadScoresFromFile(SCORESFILE, m_scores);

    // Keep only the first 2 texts (title and back button)
    m_texts.clear();

    updateScoresToTexts();
}

void LeaderboardPage::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    auto& backButton = m_mainTexts.back(); // back button is at index 1

    if (event.is<sf::Event::MouseMoved>()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (backButton.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
            m_hoverBack = true;
            backButton.setFillColor(sf::Color::Yellow);
        }
        else {
            m_hoverBack = false;
            backButton.setFillColor(sf::Color::White);
        }
    }
    if (event.is<sf::Event::MouseButtonPressed>()) {
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseEvent->button == sf::Mouse::Button::Left && m_hoverBack)
            m_backToMenu = true;
    }
}

void LeaderboardPage::draw(sf::RenderWindow& window) {
    window.draw(m_bgSprite);
    for (const auto& op : m_mainTexts)
        window.draw(op);
    for (const auto& text : m_texts)
        window.draw(text);
}

void LeaderboardPage::resetLBPage()
{
    m_backToMenu = false;
    m_hoverBack = false;
    m_mainTexts.back().setFillColor(sf::Color::White);
}

// Score entries (dynamic)
void LeaderboardPage::updateScoresToTexts()
{
    float y = 150.f;
    for (const auto& entry : m_scores) {
        sf::Text entryText(m_font);
        entryText.setString(entry.name + ": " + std::to_string(entry.score));
        entryText.setCharacterSize(30);
        entryText.setFillColor(sf::Color::White);
        entryText.setOutlineThickness(2);
        entryText.setOutlineColor(sf::Color::Black);
        entryText.setPosition(sf::Vector2f(100.f, y));
        m_texts.push_back(entryText);
        y += 40.f;
    }
}
