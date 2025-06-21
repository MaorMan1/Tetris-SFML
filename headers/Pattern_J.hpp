#ifndef TETRIS_PATTERN_J_HPP 
#define TETRIS_PATTERN_J_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

/**
 * @class Pattern_J
 * @brief Represents the J-shaped Tetris piece.
 *
 * Inherits from CubePattern and defines rotation states,
 * color, and wall kick offsets specific to the J tetromino.
 */
class Pattern_J : public CubePattern {
public:
    /**
     * @brief Constructs the J-pattern with default pivot and rotations.
     */
    Pattern_J();

    /**
     * @brief Returns wall kick offsets for the current rotation index.
     */
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;

    /**
     * @brief Returns the color used to draw the J-pattern (Blue).
     */
    sf::Color getColor() const override;
};
#endif