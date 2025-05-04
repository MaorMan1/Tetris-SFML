#ifndef TETRIS_PATTERN_O_HPP
#define TETRIS_PATTERN_O_HPP
#include "Globals.hpp"
#include "CubePattern.hpp"

class Pattern_O : public CubePattern {
public:
    Pattern_O();
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;
    sf::Color getColor() const override; 
};

#endif