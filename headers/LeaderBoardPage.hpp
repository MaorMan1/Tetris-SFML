#ifndef TETRIS_LEADERBOARDPAGE_HPP
#define TETRIS_LEADERBOARDPAGE_HPP

#include "Page.hpp"
#include "ScoreEntry.hpp"
#include <vector>

/**
 * @class LeaderboardPage
 * @brief Displays the Top 5 high scores in the Tetris game.
 *
 * This class loads the scores from file and renders them along with a "Back to Menu" button.
 * It inherits from the abstract Page class and implements draw/event logic accordingly.
 */
class LeaderboardPage : public Page {
public:
    /**
     * @brief Constructs the leaderboard page and loads scores.
     * @param window Reference to the window for proper layout sizing.
     */
    LeaderboardPage(sf::RenderWindow& window);

    /**
     * @brief Handles mouse events like hover and click on the back button.
     */
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

    /**
     * @brief Draws the background, title, back button, and scores.
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Loads scores from the file and updates the text vector.
     */
    void loadScores(); // can be called from outside to reload

    /**
     * @brief Resets the state of the page when returning to it.
     */
    void resetLBPage();

    /**
     * @brief Converts the score entries to drawable sf::Text objects.
     */
    void updateScoresToTexts();

private:
    sf::Font m_font;                        ///< Font used for all texts
    std::vector<sf::Text> m_mainTexts;      ///< Title and back button
    std::vector<sf::Text> m_texts;          ///< Score entries (Top 5)
    sf::Sprite m_bgSprite;                  ///< Background image
    bool m_hoverBack;                       ///< Whether back button is hovered
    std::vector<ScoreEntry> m_scores;       ///< Loaded scores
};

#endif
