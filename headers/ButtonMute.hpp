#ifndef TETRIS_BUTTONMUTE_HPP
#define TETRIS_BUTTONMUTE_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

// Button to toggle sound (mute/unmute)
class ButtonMute : public UIButton {
public:
    ButtonMute();

    // Toggles mute state and updates icon
    Button onClick() override;

    // Resets to unmuted state
    void reset() override;

private:
    bool m_muted = false;  // Current mute status
    std::vector<sf::IntRect> m_muteSprites;   // Sprites for mute icon
    std::vector<sf::IntRect> m_unmuteSprites; // Sprites for unmute icon
};
#endif