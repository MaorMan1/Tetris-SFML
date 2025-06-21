#ifndef TETRIS_PATTERN_I_HPP
#define TETRIS_PATTERN_I_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"
#include "GamePlayPage.hpp"

/**
 * @class Pattern_I
 * @brief Represents the I-shaped Tetris piece.
 *
 * Inherits from CubePattern and defines the I shape's color, initial position,
 * rotation states, and wall kick offsets specific to this piece.
 */
class Pattern_I : public CubePattern {
public:
    /**
     * @brief Constructs the I pattern with default pivot and shape offsets.
     */
    Pattern_I();

    /**
     * @brief Returns the kick offsets used when rotating the piece.
     * @param rotationIndex The current rotation index (0 or 1).
     */
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;

    /**
     * @brief Returns the color representing the I pattern.
     */
    sf::Color getColor() const override;
};

#endif 