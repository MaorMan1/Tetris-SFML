#ifndef TETRIS_PATTERN_L_HPP
#define TETRIS_PATTERN_L_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

class Pattern_L : public CubePattern {
public:
    Pattern_L();
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;
    sf::Color getColor() const override;
};

#endif
