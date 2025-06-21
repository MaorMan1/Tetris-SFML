#ifndef TETRIS_PATTERN_Z_HPP
#define TETRIS_PATTERN_Z_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

/**
 * @class Pattern_Z
 * @brief Represents the Z-shaped Tetris piece.
 *
 * Contains two rotation states (horizontal and vertical), color,
 * and wall kick offsets for smooth rotation transitions.
 */
class Pattern_Z : public CubePattern {
public:
    /**
     * @brief Constructs the Z-pattern with default shape and pivot.
     */
    Pattern_Z();

    /**
     * @brief Returns wall kick offsets for the given rotation index.
     */
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;

    /**
     * @brief Returns the color of the Z-piece (Red).
     */
    sf::Color getColor() const override;
};

#endif
