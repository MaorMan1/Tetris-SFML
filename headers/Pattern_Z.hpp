#ifndef TETRIS_PATTERN_Z_HPP
#define TETRIS_PATTERN_Z_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

class Pattern_Z : public CubePattern {
public:
    Pattern_Z();
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;
    sf::Color getColor() const override;
};

#endif
