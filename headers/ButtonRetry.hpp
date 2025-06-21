#ifndef TETRIS_BUTTONRETRY_HPP
#define TETRIS_BUTTONRETRY_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

// Button to restart the current level or game
class ButtonRetry : public UIButton {
public:
    ButtonRetry();

    // Trigger retry logic
    Button onClick() override;

    // Reset button to default visual state
    void reset() override;
};

#endif