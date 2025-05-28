#ifndef TETRIS_BUTTONRETRY_HPP
#define TETRIS_BUTTONRETRY_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "UIButton.hpp"
#include "Globals.hpp"

class ButtonRetry: public UIButton {
public:
    ButtonRetry();
    void onClick() override;
};

#endif