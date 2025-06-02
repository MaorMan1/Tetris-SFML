#ifndef TETRIS_LEADERBOARDPAGE_HPP
#define TETRIS_LEADERBOARDPAGE_HPP

#include "Page.hpp"
#include "ScoreEntry.hpp"
#include <vector>

class LeaderboardPage : public Page {
public:
    LeaderboardPage(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;

    void loadScores(); // public for reloading

    void resetLBPage();

    void updateScoresToTexts();

private:
    sf::Font m_font;
    std::vector<sf::Text> m_mainTexts; 
    std::vector<sf::Text> m_texts;
    sf::Sprite m_bgSprite;
    bool m_hoverBack;

    std::vector<ScoreEntry> m_scores;
};

#endif
