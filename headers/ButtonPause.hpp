#ifndef TETRIS_BUTTONPAUSE_HPP
#define TETRIS_BUTTONPAUSE_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

// Button to toggle pause/play state in the game
class ButtonPause : public UIButton {
public:
    ButtonPause();

    // Toggle between paused and playing
    Button onClick() override;

    // Reset to default (playing)
    void reset() override;

private:
    bool m_paused = false;  // Current pause state
    std::vector<sf::IntRect> m_pauseSprites;  // Pause icons
    std::vector<sf::IntRect> m_playSprites;   // Play icons
};

#endif