#ifndef TETRIS_PATTERN_O_HPP
#define TETRIS_PATTERN_O_HPP

#include "Globals.hpp"
#include "CubePattern.hpp"

/**
 * @class Pattern_O
 * @brief Represents the O-shaped (square) Tetris piece.
 *
 * The O-piece has no rotation effect, so it has only one static configuration
 * and a single no-op kick offset.
 */
class Pattern_O : public CubePattern {
public:
    /**
     * @brief Constructs the O-pattern with a fixed rotation and pivot.
     */
    Pattern_O();

    /**
     * @brief Returns an empty or no-op kick offset.
     */
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;

    /**
     * @brief Returns the O-piece's color (Yellow).
     */
    sf::Color getColor() const override;
};

#endif