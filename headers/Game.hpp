#ifndef TETRIS_GAME_HPP
#define TETRIS_GAME_HPP
#include <SFML/Audio.hpp>
#include "MenuMain.hpp"
#include "AboutPage.hpp"
#include "Pattern_I.hpp"

class Game {
public:
	void run();
	
private:
    void handlePageSwitching(sf::RenderWindow& window);
    void loadResources();
    bool isDelayedHandle(sf::RenderWindow& window);
    void startMusicFade(const std::string& musicKey, float durationSeconds);

    std::unique_ptr<MenuMain> m_menu;
    std::unique_ptr<AboutPage> m_about;
    std::unique_ptr<GamePlayPage> m_game;

    Page* m_currentPage = nullptr;

    DelayTimer m_delay;
    bool m_pendingExit = false;
    sf::Music* m_musicToFade = nullptr;
    bool m_fadeMusic = false;
};

#endif 