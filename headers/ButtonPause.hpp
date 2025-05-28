#ifndef TETRIS_BUTTONPAUSE_HPP
#define TETRIS_BUTTONPAUSE_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

class ButtonPause : public UIButton {
public:
    ButtonPause();
    void onClick() override;

private:
    std::vector<sf::IntRect> m_pauseSprites;
    std::vector<sf::IntRect> m_playSprites;
};

#endif