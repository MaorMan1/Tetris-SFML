#include "GamePlayPage.hpp"
#include "Pattern_I.hpp"
#include "Pattern_O.hpp"
#include "Pattern_T.hpp"
#include "Pattern_J.hpp"
#include "Pattern_L.hpp"
#include "Pattern_S.hpp"
#include "Pattern_Z.hpp"

GamePlayPage::GamePlayPage(sf::RenderWindow& window) :
    m_music(&ResourcesManager::get().getMusic("game_play_music")),
    m_board(window.getSize()),
    m_nextPiece(reloadRandomPattern()),
    m_fireTrail(std::make_unique<FireTrailAnimation>()),
    m_gameOver(false),
    m_downHeld(false),
    m_pause(false),
    m_pauseText(ResourcesManager::get().getFont("main")),
    m_countdownActive(true),
    m_uiBar(window.getSize(), m_board.getBlockSize(), m_board.getOffset())/*,
    m_mouseLeftHeld(false)*/
{
    // Set hover mouse effect
    m_hoverCircle.setRadius(20.f); // Radius of the hover effect
    m_hoverCircle.setFillColor(sf::Color(255, 255, 0, 100)); // Yellowish with transparency
    m_hoverCircle.setOrigin(sf::Vector2f(m_hoverCircle.getRadius(), m_hoverCircle.getRadius())); // Centered

    m_music->setLooping(true);
    setPauseText();
    //m_music->setVolume(100.f); // Adjust as needed
    
    // Done here and not in the initialize to make sure that current piece spawned after next piece reload to avoid unknown behavior:
    m_currentPiece = spawnNextPattern();
    clear();
}

void GamePlayPage::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    // Name writing events in game over - new high score scenario.
    if (m_gameOver && m_highScoreEligible) 
        nameWritingNewHighScoreEvent(event);

    // Keyboard events
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
    // Mouse events
    if (event.is<sf::Event::MouseButtonPressed>()) {
        ResourcesManager::get().getSound("mouse_click").play();
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseEvent->position.x), static_cast<float>(mouseEvent->position.y));
            m_uiBar.mouseButtonClick(mousePos);
        }
    }
    if (event.is<sf::Event::MouseButtonReleased>()) {
        const auto& mouseEvent = event.getIf<sf::Event::MouseButtonReleased>();
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            handleButtonClick(m_uiBar.mouseButtonHandle());
        }
    }
}

void GamePlayPage::draw(sf::RenderWindow& window)
{
    if (m_countdownActive) { // 3 second count in the beginning
        m_board.draw(window, 100); // oppacity alpha is 100 out of 255
        m_uiBar.draw(window, 100);
        drawCountdown(window);
        return; // Don't draw piece or anything else
    }

    // Game over draw handle
    if (m_gameOver) {
        m_board.draw(window, 100); // oppacity alpha is 100 out of 255
        m_uiBar.draw(window, 100);
        drawGameOverText(window);             // draws centered PNG
        return;
    }

    if (m_pause) {
        m_board.draw(window, 100); // oppacity alpha is 100 out of 255
        m_uiBar.draw(window);
        if (m_currentPiece)
            m_currentPiece->draw(window, m_board, 100);
        drawPauseText(window);

        // Draw hover circle if on text
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
        m_hoverCircle.setPosition(worldPos);
        if (m_pauseText.getGlobalBounds().contains(worldPos)) {
            window.draw(m_hoverCircle);
        }
        return;
    }

    // Push shake offset
    sf::View view = window.getView();
    sf::Vector2f shakeOffset = m_shake.getShakeOffset();
    view.move(shakeOffset);
    window.setView(view);

    // Draw board normally
    m_board.draw(window);
    m_uiBar.draw(window);

    // check
    for (const auto& popup : m_scorePopups) {
        popup.draw(window);
    }

    // For safe usage
    if (!m_nextPiece) 
        m_nextPiece = reloadRandomPattern();
     
    if (m_fireTrail)
        m_fireTrail->draw(window, m_board.getBlockSize(), m_board.getOffset());
    if (m_currentPiece)
        m_currentPiece->draw(window, m_board);
    if (m_currentPiece)
        m_currentPiece->drawGhost(window, m_board, getComputedGhostPivotPiece());

    // Draw explosion animation
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
    m_board.clear();
    m_currentPiece = nullptr;
    m_nextPiece = reloadRandomPattern(); 
    m_uiBar.updateNextPiece(m_nextPiece.get());

    m_countdownActive = true;
    m_startDelay.start(4.f);
    m_lastNumCounted = "";

    m_animations.clear();
    m_pendingClearLines.clear();

    m_downHeld = false;
    m_gameOver = false;
    m_pause = false;
    m_gameOverDelay.reset();

    m_backToMenu = false;
    m_score = 0;
    m_uiBar.updateScore(m_score);
    m_uiBar.resetButtons();
    m_music->setVolume(100.f); // 100% volume
}

void GamePlayPage::update(const sf::Time deltaTime, const sf::RenderWindow& window)
{
    if (m_countdownActive) {
        if (m_startDelay.isDone()) {
            m_countdownActive = false;
            //m_nextPiece = reloadRandomPattern();
            m_currentPiece = spawnNextPattern(); // spawn after countdown
            playGPBackGroundMusic();
            m_gravity.start(1.f);
        }
        return; // Don't update game until countdown done
    }
    if (m_gameOver) {
        if (m_gameOverDelay.isDone() && !m_highScoreEligible) { 
            m_backToMenu = true;
        }
        return;
    }
    if (m_pause) {
        m_uiBar.update();
        return;
    }

    m_uiBar.update();
    m_shake.update(deltaTime);
    updateAnimations(deltaTime);

    // check - Update score popups
    for (auto it = m_scorePopups.begin(); it != m_scorePopups.end(); ) {
        it->update(deltaTime);
        if (it->isFinished())
            it = m_scorePopups.erase(it);
        else
            ++it;
    }

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

    m_currentPiece = spawnNextPattern();
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
        ResourcesManager::get().getSound("lock_piece").play();
        if (m_fireTrail) m_fireTrail->stop();
        auto affectedRows = m_board.lockPiece(*m_currentPiece);
        auto fullLines = m_board.findFullLines(affectedRows);

        if (!fullLines.empty()) {
            addScore(static_cast<int>(fullLines.size()));
            m_uiBar.updateScore(m_score);
            m_board.clearLinesFromGrid(fullLines);
            m_shake.start(fullLines.size() /** 2.f*/, fullLines.size() /** 5.f*/); //?

            auto explosionAnim = std::make_unique<LineClearAnimation>();
            explosionAnim->start(fullLines);
            m_animations.push_back(std::move(explosionAnim));

            m_pendingClearLines = fullLines;
            m_currentPiece.reset(); // Wait for clear to spawn new one
        }
        else {
            m_currentPiece = spawnNextPattern();
            if (isGameOver()){
                stopGPBackGroundMusic();
                m_currentPiece.reset();
            }
            //m_gravity.speedUp();
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
            if(!checkForHighScore())
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
}


std::unique_ptr<CubePattern> GamePlayPage::spawnNextPattern()
{
    std::unique_ptr<CubePattern> toSpawn = std::move(m_nextPiece);
    m_nextPiece = reloadRandomPattern();
    m_uiBar.updateNextPiece(m_nextPiece.get());
    return toSpawn;
}

std::unique_ptr<CubePattern> GamePlayPage::reloadRandomPattern()
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

// Set the game over's sprite and returns it
sf::Sprite GamePlayPage::getGameOverSprite(const sf::Vector2u windowSize) const
{
    sf::Sprite sprite(ResourcesManager::get().getTexture("game_over_pic"));
    auto GOFrame = sf::IntRect(sf::Vector2i(77, 0), sf::Vector2i(226, 62));
    sprite.setTextureRect(GOFrame);
    sprite.setScale(sf::Vector2f(1.5f, 1.5f));
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setPosition(
        sf::Vector2f(
            windowSize.x / 2.f - bounds.size.x / 2.f,
            windowSize.y / 3.f - bounds.size.y / 2.f
        )
    );
    return sprite;
}

// Set the game over's text and returns it
sf::Text GamePlayPage::getGameOverScore(const sf::Vector2u windowSize) const
{
    sf::Text scoreText(ResourcesManager::get().getFont("main"));
    scoreText.setString("Your score is: " + std::to_string(m_score));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(2);

    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(sf::Vector2f(scoreBounds.size.x / 2.f, scoreBounds.size.y / 2.f));
    scoreText.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    return scoreText;
}

void GamePlayPage::drawGameOverText(sf::RenderWindow& window) {
    // Draw the Game Over sprite
    window.draw(getGameOverSprite(window.getSize()));

    // Draw the score
    window.draw(getGameOverScore(window.getSize()));

    // If eligible for top 5, draw name entry prompt
    if (m_highScoreEligible) 
        drawNewScorePrompt(window);
}

void GamePlayPage::saveHighScore() {
    std::vector<ScoreEntry> scores;
    loadScoresFromFile(SCORESFILE, scores);

    scores.push_back({ m_enteredName, m_score });
    std::sort(scores.begin(), scores.end());
    if (scores.size() > 5)
        scores.resize(5);

    saveScoresToFile(SCORESFILE, scores);
}

void GamePlayPage::drawCountdown(sf::RenderWindow& window)
{
    float secondsLeft = m_startDelay.getDuration().asSeconds() - m_startDelay.getElapsed().asSeconds();

    std::string displayText;
    if (secondsLeft > 3.0f)
        displayText = "3";
    else if (secondsLeft > 2.0f)
        displayText = "2";
    else if (secondsLeft > 1.0f)
        displayText = "1";
    else
        displayText = "Go!";
    if (displayText != m_lastNumCounted) {
        m_lastNumCounted = displayText;
        ResourcesManager::get().getSound(m_lastNumCounted).play();
    }
    sf::Text text(ResourcesManager::get().getFont("main"));
    text.setString(m_lastNumCounted);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);

    // Center the text
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    text.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

    window.draw(text);
}

void GamePlayPage::stopGPBackGroundMusic()
{
    if (m_music->getStatus() == sf::SoundSource::Status::Playing ||
        m_music->getStatus() == sf::SoundSource::Status::Paused)
        m_music->stop(); // Also reset to the beginning of the song and thats why if paused
}

void GamePlayPage::pauseGPBackGroundMusic()
{
    if (m_music->getStatus() == sf::SoundSource::Status::Playing)
        m_music->pause();
}

void GamePlayPage::playGPBackGroundMusic()
{
    if (m_music->getStatus() == sf::SoundSource::Status::Stopped ||
        m_music->getStatus() == sf::SoundSource::Status::Paused)
        m_music->play();
}

void GamePlayPage::addScore(int linesCleared)
{
    int scoreToAdd = 0;
    switch (linesCleared) {
    case 1: scoreToAdd = 100; break;
    case 2: scoreToAdd = 300; break;
    case 3: scoreToAdd = 500; break;
    case 4: scoreToAdd = 800; break;
    default: break;
    }
    m_score += scoreToAdd;

    if (scoreToAdd == 0) return;

    //TODO SOUND EFFECT!!!
    //TODO NEW FONT

    sf::Vector2f centerBoard = {
    m_board.getOffset().x + WIDTH * m_board.getBlockSize() / 2.f,
    m_board.getOffset().y + HEIGHT * m_board.getBlockSize() / 2.f
    };

    std::string text = "+" + std::to_string(scoreToAdd);
    m_scorePopups.emplace_back(ResourcesManager::get().getFont("main"), centerBoard, text);
}

int GamePlayPage::getScore() const
{
    return m_score;
}

void GamePlayPage::handleButtonClick(const Button btnClk)
{
    switch (btnClk)
    {
    case Button::Pause:
        pauseGPBackGroundMusic();
        m_pause = true;
        break;
    case Button::Play:
        playGPBackGroundMusic();
        m_pause = false;
        break;
    case Button::Retry:
        stopGPBackGroundMusic();
        clear();
        break;
    case Button::Home:
        stopGPBackGroundMusic();
        m_backToMenu = true;
        break;
    case Button::Mute:
        m_music->setVolume(0.f); // 0% volume
        break;
    case Button::Unmute:
        m_music->setVolume(100.f); // 100% volume
        break;
    default:
        break;
    }
}

void GamePlayPage::setPauseText()
{
    // Generate random RGB values
    int r = (rand() % 256),
        g = (rand() % 256),
        b = (rand() % 256);
    sf::Color randomOutlineColor(r, g, b);

    string msg = "Paused,\nPress 'Play' button to continue...";
    m_pauseText.setString(msg);
    m_pauseText.setCharacterSize(20); // Adjust to your preference
    m_pauseText.setFillColor(sf::Color::White);
    m_pauseText.setOutlineColor(randomOutlineColor);
    m_pauseText.setOutlineThickness(2.f);

    // Center text on the Board area (not the whole window)
    sf::FloatRect bounds = m_pauseText.getLocalBounds();
    m_pauseText.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));

    sf::Vector2f centerBoard;
    centerBoard.x = m_board.getOffset().x + WIDTH * m_board.getBlockSize() / 2.f;
    centerBoard.y = m_board.getOffset().y + HEIGHT * m_board.getBlockSize() / 2.f;

    m_pauseText.setPosition(centerBoard);
}

void GamePlayPage::drawPauseText(sf::RenderWindow& window)
{
    window.draw(m_pauseText);
}

bool GamePlayPage::checkForHighScore(){
    std::vector<ScoreEntry> scores;
    loadScoresFromFile(SCORESFILE, scores);

    if (scores.size() < 5 || m_score > scores.back().score) {
        m_writingDelay.start(0.5f);
        m_highScoreEligible = true;
        m_enteredName.clear();
    }
    return m_highScoreEligible;
}

void GamePlayPage::drawNewScorePrompt(sf::RenderWindow& window)
{
    sf::Text namePrompt(ResourcesManager::get().getFont("main"));
    namePrompt.setString("New High Score! Enter your name:");
    namePrompt.setCharacterSize(20);
    namePrompt.setFillColor(sf::Color::Yellow);
    namePrompt.setPosition(sf::Vector2f(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f + 50.f));

    sf::Text nameEntry(ResourcesManager::get().getFont("main"));
    if (m_writingLineShown)  // 1 sec delay from "|" to hide it
        nameEntry.setString(m_enteredName);
    else
        nameEntry.setString(m_enteredName + "|");

    if (m_writingDelay.isDone()) {
        m_writingLineShown = !m_writingLineShown;
        m_writingDelay.start(0.5f);
    }
    nameEntry.setCharacterSize(24);
    nameEntry.setFillColor(sf::Color::Cyan);
    nameEntry.setPosition(sf::Vector2f(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f + 80.f));

    sf::Text pressPrompt(ResourcesManager::get().getFont("main"));
    pressPrompt.setString("Press 'Enter' to continue..");
    pressPrompt.setCharacterSize(20);
    pressPrompt.setFillColor(sf::Color::Yellow);
    pressPrompt.setPosition(sf::Vector2f(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f + 110.f));

    window.draw(namePrompt);
    window.draw(nameEntry);
    window.draw(pressPrompt);
}

void GamePlayPage::nameWritingNewHighScoreEvent(const sf::Event& event)
{
    if (event.is<sf::Event::TextEntered>()) {
        auto unicode = event.getIf<sf::Event::TextEntered>()->unicode;
        if (unicode == '\b') { // Backspace
            if (!m_enteredName.empty())
                m_enteredName.pop_back();
        }
        else if (unicode == '\r' || unicode == '\n') { // Enter
            saveHighScore();
            m_highScoreEligible = false;
            m_gameOverDelay.start(0.7f); // delay before switching page to menu
        }
        else if (m_enteredName.size() < 10 && unicode < 128) { // Limit name length
            m_enteredName += static_cast<char>(unicode);
        }
    }
}
