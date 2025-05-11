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
    m_fireTrail(std::make_unique<FireTrailAnimation>()),
    m_gameOver(false),
    m_downHeld(false)
{
    //m_backToMenu = false;
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
    if (m_gameOver) {
        m_board.draw(window, 100); // oppacity alpha is 100 out of 255
        drawGameOverText(window);             // draws centered PNG
        return;
    }
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
    if (m_currentPiece)
        m_currentPiece->drawGhost(window, m_board, getComputedGhostPivotPiece());


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

void GamePlayPage::clear()
{
    // Clear grid to reuse
    m_board.clear();
    // Reset gameplay state
    m_currentPiece = spawnRandomPattern();
    m_gravity.start(1.f);

    m_animations.clear();
    m_pendingClearLines.clear();

    m_downHeld = false;
    m_gameOver = false;
    m_gameOverDelay.reset();

    m_backToMenu = false;
}

void GamePlayPage::update(const sf::Time deltaTime)
{
    if (m_gameOver) {
        if (m_gameOverDelay.isDone()) {
            m_backToMenu = true;
        }
        return;
    }
    //const sf::Time deltaTime = sf::seconds(1.f / 60.f); // Target frame time (~60 FPS)

    m_shake.update(deltaTime);
    updateAnimations(deltaTime);

    if (!m_animations.empty())
        return; // Wait for all animations to complete

    if (handlePendingLineClears())
        return; // Skip gravity if lines were just cleared

    if (!m_currentPiece)
        return;

    handleGravity();

    updateFireTrail(deltaTime);
}

void GamePlayPage::updateAnimations(sf::Time dt)
{
    for (auto it = m_animations.begin(); it != m_animations.end(); ) {
        (*it)->update(dt);
        if ((*it)->isFinished())
            it = m_animations.erase(it);
        else
            ++it;
    }
}

bool GamePlayPage::handlePendingLineClears()
{
    if (m_pendingClearLines.empty())
        return false;

    m_board.clearLinesFromGrid(m_pendingClearLines);
    m_board.collapseLines(m_pendingClearLines);
    m_board.debugPrint();
    m_pendingClearLines.clear();

    m_currentPiece = spawnRandomPattern();
    m_gravity.speedUp();
    return true;
}

void GamePlayPage::handleGravity()
{
    if (!m_gravity.shouldFall())
        return;

    sf::Vector2i next = m_currentPiece->getPivot() + sf::Vector2i(0, 1);
    auto nextPositions = m_currentPiece->getPatternPositions(next);

    if (!m_board.checkCollision(nextPositions)) {
        m_currentPiece->moveDown(m_board);
    }
    else {
        if (m_fireTrail) m_fireTrail->stop();

        ResourcesManager::get().getSound("lock_piece").play();
        auto affectedRows = m_board.lockPiece(*m_currentPiece);
        auto fullLines = m_board.findFullLines(affectedRows);

        if (!fullLines.empty()) {
            m_board.clearLinesFromGrid(fullLines);
            m_shake.start(fullLines.size() /** 2.f*/, fullLines.size() /** 5.f*/); //?

            auto explosionAnim = std::make_unique<LineClearAnimation>();
            explosionAnim->start(fullLines);
            m_animations.push_back(std::move(explosionAnim));

            m_pendingClearLines = fullLines;
            m_currentPiece.reset(); // Wait for clear to spawn new one
        }
        else {
            m_currentPiece = spawnRandomPattern();
            if (isGameOver()){
                //m_backToMenu = true;
                m_currentPiece.reset();
            }
            m_gravity.speedUp();
        }
    }

    m_gravity.reset();
}

void GamePlayPage::updateFireTrail(sf::Time dt)
{
    if (!m_downHeld || !m_currentPiece || !m_fireTrail)
        return;

    const auto& blocks = m_currentPiece->getPatternPositions(m_currentPiece->getPivot());
    if (blocks.empty()) return;

    // Compute average X (horizontal center) and max Y (bottom-most row)
    float avgCol = 0.f;
    int maxRow = 0;
    for (const auto& b : blocks) {
        avgCol += b.x;
        if (b.y > maxRow)
            maxRow = b.y;
    }
    avgCol /= blocks.size();

    float blockSize = m_board.getBlockSize();
    sf::Vector2f offset = m_board.getOffset();

    sf::Vector2f worldPos;
    worldPos.x = offset.x + avgCol * blockSize;
    worldPos.y = offset.y + (maxRow + 1) * blockSize;

    m_fireTrail->start(worldPos);
    m_fireTrail->update(dt);
}

bool GamePlayPage::isGameOver()
{
    const auto& newPieceCheck = m_currentPiece.get()->getPatternPositions(m_currentPiece.get()->getPivot());
    for (const auto& piv : newPieceCheck) {
        std::cout << piv.y << " " << piv.x << std::endl;
        if (m_board.getCell(piv.y, piv.x) != '_') {
            m_gameOver = true;
            m_gameOverDelay.start(3.0f); // delay before switching page to menu 
            break;
        }
    }
    return m_gameOver;
}

// Compute ghost pivot
sf::Vector2i GamePlayPage::getComputedGhostPivotPiece()
{
    sf::Vector2i ghostPivot = m_currentPiece->getPivot();
    while (true) {
        auto next = m_currentPiece->getPatternPositions(ghostPivot + sf::Vector2i(0, 1)); // One more step down untill colision found
        if (!m_board.checkCollision(next))
            ghostPivot.y += 1; // Moving ghost forward
        else // Collision found
            break; 
    }
    return ghostPivot;
}//git chec


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

void GamePlayPage::drawGameOverText(sf::RenderWindow& window) {
    sf::Sprite sprite(ResourcesManager::get().getTexture("game_over_pic"));
    auto GOFrame = sf::IntRect(sf::Vector2i(77, 0), sf::Vector2i(226, 62));
    sprite.setTextureRect(GOFrame);
    sprite.setScale(sf::Vector2f(1.5f, 1.5f)); // adjust
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setPosition(
        sf::Vector2f(
        window.getSize().x / 2.f - bounds.size.x / 2.f,
        window.getSize().y / 3.f - bounds.size.y / 2.f
        )
    );
    window.draw(sprite);
}