#ifndef TETRIS_GAMEPLAYPAGE_HPP
#define TETRIS_GAMEPLAYPAGE_HPP
#include "Page.hpp"
#include "Board.hpp"
#include "GravityTimer.hpp"
#include "LineClearAnimation.hpp"
#include "ShakeManager.hpp"
#include "BaseAnimation.hpp"
#include "FireTrailAnimation.hpp"
#include "UIBar.hpp"
#include "LeaderboardUtils.hpp"
#include "LeaderBoardPage.hpp"
#include "ScorePopup.hpp"


/**
 * @class GamePlayPage
 * @brief Represents the main gameplay screen for the Tetris game.
 *
 * This class handles all game logic including piece movement, line clearing, scoring,
 * animations, UI updates, music control, and game-over handling.
 *
 * It inherits from the abstract Page class, enabling polymorphic page switching from the main Game class.
 * All memory is handled via smart pointers and updated on a per-frame basis through the update() function.
 */
class GamePlayPage : public Page {
public:
    /**
     * @brief Constructs the GamePlayPage and initializes all gameplay components.
     * @param window Reference to the game window for size and positioning purposes.
     */
    GamePlayPage(sf::RenderWindow& window);

    ~GamePlayPage() = default; // All resources are managed automatically

    /**
     * @brief Handles input events such as keyboard and mouse during gameplay.
     */
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

    /**
     * @brief Draws all gameplay elements onto the window.
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Updates the game logic based on delta time.
     */
    void update(const sf::Time deltaTime, const sf::RenderWindow& window);

    /**
     * @brief Returns a raw pointer to the currently active falling piece.
     */
    CubePattern* getCurrentActivePiece() const;

    /**
     * @brief Clears the board and resets the game state to start a new session.
     */
    void clear();

    /**
     * @brief Returns the "Game Over" sprite for display.
     */
    sf::Sprite getGameOverSprite(const sf::Vector2u windowSize) const;

    /**
     * @brief Returns the score text displayed on game over.
     */
    sf::Text getGameOverScore(const sf::Vector2u windowSize) const;

    /**
     * @brief Saves the current score to the leaderboard if it's a new high score.
     */
    void saveHighScore();

private:
    // ===== Core Components =====
    Board m_board;
    std::unique_ptr<CubePattern> m_nextPiece;
    std::unique_ptr<CubePattern> m_currentPiece;
    GravityTimer m_gravity;
    ShakeManager m_shake;
    std::vector<std::unique_ptr<BaseAnimation>> m_animations;
    std::unique_ptr<FireTrailAnimation> m_fireTrail;
    std::vector<ScorePopup> m_scorePopups;

    // ===== State and Logic Flags =====
    bool m_downHeld = false;
    bool m_gameOver = false;
    bool m_countdownActive = true;
    bool m_pause = false;
    bool m_highScoreEligible = false;
    bool m_muted = false;

    // ===== Score Handling =====
    int m_score = 0;
    std::string m_enteredName;

    // ===== Delay Timers =====
    DelayTimer m_gameOverDelay;
    DelayTimer m_startDelay;
    DelayTimer m_writingDelay;
    bool m_writingLineShown = false;

    // ===== Meme Audio State =====
    DelayTimer m_memeTimer;
    bool m_memePlaying = false;

    // ===== UI & Visuals =====
    std::string m_lastNumCounted;
    sf::Text m_pauseText;
    sf::CircleShape m_hoverCircle;
    std::set<int> m_pendingClearLines;

    sf::Music* m_music = nullptr;
    sf::Music* m_gameOverMusic = nullptr;
    UIBar m_uiBar;

    // ===== Internal Helpers =====
    std::unique_ptr<CubePattern> spawnNextPattern();
    std::unique_ptr<CubePattern> reloadRandomPattern();
    sf::Vector2i getComputedGhostPivotPiece();
    void updateAnimations(sf::Time dt);
    bool handlePendingLineClears();
    void handleGravity();
    void updateFireTrail(sf::Time dt);
    bool isGameOver();
    void drawGameOverText(sf::RenderWindow& window);
    void drawCountdown(sf::RenderWindow& window);
    void stopGPBackGroundMusic();
    void playGPBackGroundMusic();
    void pauseGPBackGroundMusic();
    void addScore(int linesCleared);
    int getScore() const;
    void handleButtonClick(const Button btnClk);
    void drawPauseText(sf::RenderWindow& window);
    void setPauseText();
    bool checkForHighScore();
    void nameWritingNewHighScoreEvent(const sf::Event& event);
    void drawNewScorePrompt(sf::RenderWindow& window);
    void playRandomFunnyMeme();
    std::string memeConverter(const int& meme) const;
};

#endif
