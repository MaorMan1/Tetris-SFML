#ifndef TETRIS_ABOUT_HPP
#define TETRIS_ABOUT_HPP
#include "Page.hpp"


class AboutPage : public Page {
public:
    AboutPage(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    bool wantsToReturn() const;
    void resetAboutPage();

private:
    sf::Font m_font;
    std::vector<sf::Text> m_AboutPageList;
    sf::Sprite m_aboutBGSprite;

    bool m_hoverBack;
    bool m_backToMenu;
};
#endif 

