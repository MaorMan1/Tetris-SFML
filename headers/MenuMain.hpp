#ifndef TETRIS_MENUMAIN_HPP
#define TETRIS_MENUMAIN_HPP
#include <iostream>
#include "Page.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"

class MenuMain: public Page {
public:
	MenuMain(sf::RenderWindow& window);
	~MenuMain();

	void handleEvent(const sf::Event &event, const sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window/*, const GameState currentState*/) override;
	MenuOptions getSelection() const;
	void resetSelection();	//TOUSE

	//Handle music
	void stopMenuBackGroundMusic();
	void playMenuBackGroundMusic();

private:
    const sf::Font& m_font;
	std::vector<sf::Text> m_menuOptions;
	MenuOptions m_selected;
	sf::Music* m_music = nullptr;
	sf::Sprite m_menuBGSprite;
};
#endif
