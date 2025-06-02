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

class GamePlayPage : public Page {
public:
    GamePlayPage(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void update(const sf::Time deltaTime, const sf::RenderWindow& window);  // Later: for gravity, score, game state
    CubePattern* getCurrentActivePiece() const;
    void clear();
    sf::Sprite getGameOverSprite(const sf::Vector2u windowSize) const;
    sf::Text getGameOverScore(const sf::Vector2u windowSize) const;


private:
    Board m_board;
    std::unique_ptr<CubePattern> m_nextPiece;
    std::unique_ptr<CubePattern> m_currentPiece;
    GravityTimer m_gravity;
    ShakeManager m_shake;
    std::vector<std::unique_ptr<BaseAnimation>> m_animations;
    std::unique_ptr<FireTrailAnimation> m_fireTrail;

    bool m_downHeld;
    //bool m_mouseLeftHeld;
    bool m_gameOver;
    bool m_countdownActive;
    bool m_pause;
    int m_score = 0;

    //added
    DelayTimer m_gameOverDelay;
    DelayTimer m_startDelay;
    string m_lastNumCounted;
    sf::Text m_pauseText;
    sf::CircleShape m_hoverCircle;
    //LineClearAnimation m_lineClearAnimation;  
    std::set<int> m_pendingClearLines; 
    sf::Music* m_music = nullptr;
    UIBar m_uiBar;

    //helpers
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
    void checkForHighScore();
};

#endif
