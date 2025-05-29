#ifndef TETRIS_BUTTONBACKTOMENU_HPP
#define TETRIS_BUTTONBACKTOMENU_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

class ButtonBackToMenu : public UIButton {
public:
    ButtonBackToMenu();
    Button onClick() override;
    void reset() override;
};

#endif