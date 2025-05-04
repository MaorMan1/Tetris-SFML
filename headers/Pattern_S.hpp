#ifndef TETRIS_PATTERN_S_HPP
#define TETRIS_PATTERN_S_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

class Pattern_S : public CubePattern {
public:
    Pattern_S();
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;
    sf::Color getColor() const override;
};

#endif
