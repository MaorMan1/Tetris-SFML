#include "GamePlayPage.hpp"
#include "Pattern_I.hpp"
#include "Pattern_O.hpp"
#include "Pattern_T.hpp"
#include "Pattern_J.hpp"
#include "Pattern_L.hpp"
#include "Pattern_S.hpp"
#include "Pattern_Z.hpp"

GamePlayPage::GamePlayPage(sf::RenderWindow& window) :
    m_board(window.getSize()),
    m_currentPiece(spawnRandomPattern()),
    m_fireTrail(std::make_unique<FireTrailAnimation>())
{
    m_gravity.start(1.f);   // Initial delay of 1 second
}

void GamePlayPage::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (!m_currentPiece) return;
    if (event.is<sf::Event::KeyPressed>()) {
        const auto& key = event.getIf<sf::Event::KeyPressed>()->code;

        if (key == sf::Keyboard::Key::Left) {
            m_currentPiece->moveLeft(m_board);
        }
        else if(key == sf::Keyboard::Key::Right){
            m_currentPiece->moveRight(m_board);
        }
        else if (key == sf::Keyboard::Key::Down) {
            m_currentPiece->moveDown(m_board);
            m_downHeld = true;
        }
        else if (key == sf::Keyboard::Key::Up) {
            m_currentPiece->rotate(m_board);
        }
    }
    if (event.is<sf::Event::KeyReleased>()) {
        const auto& key = event.getIf<sf::Event::KeyReleased>()->code;

        if (key == sf::Keyboard::Key::Down) {
            m_downHeld = false;
            if (m_fireTrail) m_fireTrail->stop();
        }
    }
    // TODO - add later for mouse event if reset level or back to menu or pause
}

void GamePlayPage::draw(sf::RenderWindow& window)
{
    // Push shake offset
    sf::View view = window.getView();
    sf::Vector2f shakeOffset = m_shake.getShakeOffset();
    view.move(shakeOffset);
    window.setView(view);

    // Draw board normally
    m_board.draw(window);
    if (m_fireTrail)
        m_fireTrail->draw(window, m_board.getBlockSize(), m_board.getOffset());
    if (m_currentPiece)
        m_currentPiece->draw(window, m_board);
    

    // Draw explosion animation
    //m_lineClearAnimation.draw(window, m_board.getBlockSize(), m_board.getOffset()); //*
    for (const auto& anim : m_animations) {
        anim->draw(window, m_board.getBlockSize(), m_board.getOffset());
    }


    // Restore view
    view.move(-shakeOffset);
    window.setView(view);
}

CubePattern* GamePlayPage::getCurrentActivePiece() const
{
    return m_currentPiece.get();
}

void GamePlayPage::update()
{
    m_shake.update(sf::seconds(1.f / 60.f));  // ~60FPS

    // Always update all animations
    for (auto it = m_animations.begin(); it != m_animations.end(); ) {
        (*it)->update(sf::seconds(1.f / 60.f)); // ~60FPS
        if ((*it)->isFinished()) {
            it = m_animations.erase(it);
        }
        else {
            ++it;
        }
    }

    // Wait until ALL animations are done before proceeding
    if (!m_animations.empty())
        return;

    // If animation finished and pending clear exists, now clear
    if (!m_pendingClearLines.empty()) {
        // Clear the rows visually (make them '_')
        m_board.clearLinesFromGrid(m_pendingClearLines);

        // Collapse everything above them
        m_board.collapseLines(m_pendingClearLines);
        m_board.debugPrint();
        m_pendingClearLines.clear();

        // Spawn new piece
        m_currentPiece = spawnRandomPattern();
        m_gravity.speedUp();
        return; // After clearing, skip moving down
    }

    // Normal gameplay (gravity move down)
    if (!m_currentPiece)
        return;

    if (m_gravity.shouldFall()) {
        sf::Vector2i next = m_currentPiece->getPivot() + sf::Vector2i(0, 1);
        auto nextPositions = m_currentPiece->getPatternPositions(next);

        if (!m_board.checkCollision(nextPositions)) {
            m_currentPiece->moveDown(m_board);
        }
        else {
            if (m_fireTrail) 
                m_fireTrail->stop();

            ResourcesManager::get().getSound("lock_piece").play();
            auto affectedRows = m_board.lockPiece(*m_currentPiece);
            auto fullLines = m_board.findFullLines(affectedRows);

            if (!fullLines.empty()) {
                m_board.clearLinesFromGrid(fullLines);
                m_shake.start(fullLines.size() * 2.f, fullLines.size() * 5.f);  // Shake for 2 seconds with strength 5 pixels (each * how many cleared lines)
                //m_lineClearAnimation.start(fullLines); //*check*
                // Start animations:
                auto explosionAnim = std::make_unique<LineClearAnimation>();
                explosionAnim->start(fullLines);
                m_animations.push_back(std::move(explosionAnim));

                m_pendingClearLines = fullLines;
                m_currentPiece.reset(); // No current piece until lines are cleared
            }
            else {
                m_currentPiece = spawnRandomPattern();
                m_gravity.speedUp();
            }
        }

        m_gravity.reset();
    }

    // Update fire trail position under falling piece
    /*if (m_downHeld && m_currentPiece) {
        sf::Vector2i pivot = m_currentPiece->getPivot();
        float blockSize = m_board.getBlockSize();
        sf::Vector2f offset = m_board.getOffset();

        sf::Vector2f worldPos;
        worldPos.x = offset.x + pivot.x * blockSize - blockSize / 2.f;
        worldPos.y = offset.y + pivot.y * blockSize + blockSize * 0.5f; // Slightly below center
        if(m_fireTrail)
        if (m_fireTrail) {
            m_fireTrail->start(worldPos); // Continuously resets position
        }
    }*/
    if (m_downHeld && m_currentPiece) {
        const auto& blocks = m_currentPiece->getPatternPositions(m_currentPiece->getPivot());

        if (!blocks.empty()) {
            float blockSize = m_board.getBlockSize();
            sf::Vector2f offset = m_board.getOffset();

            // Compute average X and max Y of current piece
            float avgCol = 0.f;
            int maxRow = 0;
            for (const auto& b : blocks) {
                avgCol += b.x;
                if (b.y > maxRow)
                    maxRow = b.y;
            }
            avgCol /= blocks.size();

            sf::Vector2f worldPos;
            worldPos.x = offset.x + avgCol * blockSize;
            worldPos.y = offset.y + maxRow * blockSize + blockSize * 0.5f;

            if (m_fireTrail) {
                m_fireTrail->start(worldPos);
            }
        }
    }

    if (m_fireTrail) m_fireTrail->update(sf::seconds(1.f / 60.f));
    /*if (m_downHeld && m_fireTrail) {
        std::cout << "Fire Trail Active\n";
    }*/
}


std::unique_ptr<CubePattern> GamePlayPage::spawnRandomPattern()
{
    Patterns randomPattern = static_cast<Patterns>(rand() % static_cast<int>(Patterns::Count));

    switch (randomPattern) {
    case Patterns::I:
        return std::make_unique<Pattern_I>();
    case Patterns::O:
        return std::make_unique<Pattern_O>();
    case Patterns::T:
        return std::make_unique<Pattern_T>();
    case Patterns::J:
        return std::make_unique<Pattern_J>();
    case Patterns::L:
        return std::make_unique<Pattern_L>();
    case Patterns::S:
        return std::make_unique<Pattern_S>();
    case Patterns::Z:
        return std::make_unique<Pattern_Z>();
    default:
        return nullptr;
    }
}


