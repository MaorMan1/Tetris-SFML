#include "Game.hpp"
#include <cstdlib>
#include <ctime>

void Game::run()
{
    // Seeding random by curr time for the rest of the game
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Tetris remake");
    loadResources();

    m_menu = std::make_unique<MenuMain>(window);
    m_about = std::make_unique<AboutPage>(window);
    m_game = std::make_unique<GamePlayPage>(window);
    // TODO - m_leaderboard ...
    Board board(window.getSize());

    m_currentPage = m_menu.get();

    sf::Clock mainClock;
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent()) {
            if (m_delay.isActive()) continue;
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::Resized>()) {
                board.updateBlockSize(window.getSize());
            }
            m_currentPage->handleEvent(*event, window);  // polymorphic
        }
        if (isDelayedHandle(window)) 
            continue;
        // Take the passed loop time for delta time
        sf::Time deltaTime = mainClock.restart();
        // Page case
        handlePageSwitching(window, deltaTime);

        window.clear();
        m_currentPage->draw(window);
        window.display();
    }
}

void Game::handlePageSwitching(sf::RenderWindow& window, const sf::Time deltaTime)
{
    auto& pageSwitchSound = ResourcesManager::get().getSound("page_transition");
    
    if (MenuMain* m = dynamic_cast<MenuMain*>(m_currentPage)) {
        switch (m->getSelection()) { // Option selected
        case MenuOptions::About:
            pageSwitchSound.play();
            m_currentPage = m_about.get();
            break;
        case MenuOptions::Exit:
            pageSwitchSound.play();
            m_pendingExit = true;
            startMusicFade("menu", 1.0f);
            break;
        case MenuOptions::Play: 
            pageSwitchSound.play();
            m_menu.get()->stopMenuBackGroundMusic();
            m_menu.get()->resetSelection();
            m_currentPage = m_game.get();
            m_game.get()->clear();
            break;
        default:
            break;
        }
    }
    else if (AboutPage* about = dynamic_cast<AboutPage*>(m_currentPage)) {
        if (about->wantsToReturn()) { // Back button clicked            
            goBackToMenuProcedure();
            pageSwitchSound.play();
        }
    }
    else if(GamePlayPage* gp = dynamic_cast<GamePlayPage*>(m_currentPage)) {
        if (gp->wantsToReturn()) {
            goBackToMenuProcedure();
            pageSwitchSound.play(); 
            m_menu.get()->playMenuBackGroundMusic();
            // show gameover score and stuff
        }
        else {
            gp->update(deltaTime, window); // Gameplay logic with gravity
        }
    }
}

void Game::loadResources()
{
    try {
        ResourcesManager::get().loadFont("main", "resources/Arial.ttf");
        ResourcesManager::get().loadMusic("menu", "resources/Menu_Music.ogg");
        ResourcesManager::get().loadSound("page_transition", "resources/SwitchPage.wav");
        ResourcesManager::get().loadSound("mouse_click", "resources/MouseClick.wav");
        ResourcesManager::get().loadTexture("menu_bg_pic", "resources/menuBackGroundPic.jpeg");
        ResourcesManager::get().loadTexture("about_bg_pic", "resources/aboutPageBGPic.jpeg");
        ResourcesManager::get().loadSound("before_explosion", "resources/BeforeExplosion.wav");
        ResourcesManager::get().loadSound("explosion_sound", "resources/ClearLineExplosion.wav");
        ResourcesManager::get().loadMusic("game_play_music", "resources/GamePlayMusic.ogg");
        // TODO: change this horrible sound:
        ResourcesManager::get().loadSound("lock_piece", "resources/LockPiecec.wav");
        ResourcesManager::get().loadTexture("block_explosion", "resources/TetrisBlockExplosion.png");
        ResourcesManager::get().loadTexture("game_over_pic","resources/GameOverSign.png");
        ResourcesManager::get().loadTexture("fire_trail", "resources/MovingDownFastNew.png");
        ResourcesManager::get().loadTexture("ui_bar_bg", "resources/BarBG.png");
        ResourcesManager::get().loadTexture("buttons", "resources/Buttons.png");
        // Robotic counter sounds:
        ResourcesManager::get().loadSound("3", "resources/3Count.wav");
        ResourcesManager::get().loadSound("2", "resources/2Count.wav");
        ResourcesManager::get().loadSound("1", "resources/1Count.wav");
        ResourcesManager::get().loadSound("Go!", "resources/GoCount.wav");
    }
    catch (const std::exception& e) {
        std::cerr << "Resource error: " << e.what() << std::endl;
        return;
    }
}

// Delay check
bool Game::isDelayedHandle(sf::RenderWindow& window)
{
    if (!m_delay.isActive())
        return false;

    if (m_delay.isDone()) {
        m_delay.reset();
        m_fadeMusic = false;
        m_musicToFade = nullptr;

        if (m_pendingExit) {
            if (m_musicToFade)
                m_musicToFade->stop();
            window.close();
            return true;
        }

        return false;
    }
    if (m_fadeMusic && m_musicToFade) {
        float elapsed = m_delay.getElapsed().asSeconds();
        float duration = m_delay.getDuration().asSeconds();

        float volume = 100.f * (1.f - elapsed / duration);
        m_musicToFade->setVolume(std::max(0.f, volume));
    }


    window.clear();
    m_currentPage->draw(window);
    window.display();
    return true;
}

void Game::startMusicFade(const std::string& musicKey, float durationSeconds)
{
    m_musicToFade = &ResourcesManager::get().getMusic(musicKey);
    m_fadeMusic = true;
    m_delay.start(durationSeconds);
}

void Game::goBackToMenuProcedure()
{
    m_game->clear();
    m_menu->resetSelection();
    m_currentPage = m_menu.get();
    m_about.get()->resetAboutPage();
}
