#ifndef TETRIS_BUTTONBACKTOMENU_HPP
#define TETRIS_BUTTONBACKTOMENU_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

// Button to return to main menu (Home)
class ButtonBackToMenu : public UIButton {
public:
    ButtonBackToMenu();

    // What happens when button is clicked
    Button onClick() override;

    // Reset button state (called after navigation or UI reset)
    void reset() override;
};

#endif