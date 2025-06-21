#ifndef TETRIS_MENUMAIN_HPP
#define TETRIS_MENUMAIN_HPP
#include <iostream>
#include "Page.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"

/**
 * @class MenuMain
 * @brief Represents the main menu screen in the Tetris game.
 *
 * Displays selectable options such as Play, About, Leaders Board, and Exit.
 * Handles background music, hover/click interactions, and page switching.
 */
class MenuMain: public Page {
public:
	/**
	 * @brief Constructs the main menu and loads background/music.
	 */
	MenuMain(sf::RenderWindow& window);
	/**
	 * @brief Destructor — stops menu music on cleanup.
	 */
	~MenuMain();

    /**
     * @brief Handles mouse interaction events (hover/click).
     */
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;

    /**
     * @brief Draws menu background and all option buttons.
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Returns the menu option selected by the user.
     */
    MenuOptions getSelection() const;

    /**
     * @brief Resets selection state and option colors.
     */
    void resetSelection();

    /**
     * @brief Stops the looping menu background music.
     */
    void stopMenuBackGroundMusic();

    /**
     * @brief Plays the looping menu background music.
     */
    void playMenuBackGroundMusic();

private:
    const sf::Font& m_font;
	sf::Color  m_fillColor;
	sf::Color  m_outlineColor;
	std::vector<sf::Text> m_menuOptions;
	MenuOptions m_selected;
	sf::Music* m_music = nullptr;
	sf::Sprite m_menuBGSprite;
	std::string m_pendingClick;
};
#endif
