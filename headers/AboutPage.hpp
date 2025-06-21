#ifndef TETRIS_ABOUT_HPP
#define TETRIS_ABOUT_HPP

#include "Page.hpp"


// Represents the About screen of the game.
// Displayed after clicking the About button from the main menu.
class AboutPage : public Page {
public:
    AboutPage(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    void resetAboutPage();  // Resets internal flags and styles

private:
    sf::Font m_font;                     // Font used for texts
    std::vector<sf::Text> m_AboutPageList; // Holds title, description, and back button
    sf::Sprite m_aboutBGSprite;         // Background image for the page
    bool m_hoverBack = false;           // Hover state for back button
};
#endif 

