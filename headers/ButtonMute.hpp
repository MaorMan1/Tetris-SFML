#ifndef TETRIS_BUTTONMUTE_HPP
#define TETRIS_BUTTONMUTE_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

class ButtonMute : public UIButton {
public:
    ButtonMute();
    Button onClick() override;
    void reset() override;

private:
    bool m_muted;
    std::vector<sf::IntRect> m_muteSprites;
    std::vector<sf::IntRect> m_unmuteSprites;
};

#endif