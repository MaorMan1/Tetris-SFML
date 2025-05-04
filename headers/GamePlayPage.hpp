#ifndef TETRIS_GAMEPLAYPAGE_HPP
#define TETRIS_GAMEPLAYPAGE_HPP
#include "Page.hpp"
#include "Board.hpp"
#include "GravityTimer.hpp"
#include "LineClearAnimation.hpp"
#include "ShakeManager.hpp"
#include "BaseAnimation.hpp"
#include "FireTrailAnimation.hpp"

class GamePlayPage : public Page {
public:
    GamePlayPage(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void update();  // Later: for gravity, score, game state
    CubePattern* getCurrentActivePiece() const;

private:
    Board m_board;
    std::unique_ptr<CubePattern> m_currentPiece;
    GravityTimer m_gravity;
    ShakeManager m_shake;

    std::vector<std::unique_ptr<BaseAnimation>> m_animations;

    std::unique_ptr<FireTrailAnimation> m_fireTrail;
    bool m_downHeld = false;

    //LineClearAnimation m_lineClearAnimation;  
    std::set<int> m_pendingClearLines; 

    std::unique_ptr<CubePattern> spawnRandomPattern(); 
};

#endif
