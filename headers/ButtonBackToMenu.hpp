#ifndef TETRIS_BUTTONBACKTOMENU_HPP
#define TETRIS_BUTTONBACKTOMENU_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

class ButtonBackToMenu : public UIButton {
public:
    ButtonBackToMenu();
    void onClick() override;
};

#endif