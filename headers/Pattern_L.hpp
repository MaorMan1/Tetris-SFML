#ifndef TETRIS_PATTERN_L_HPP
#define TETRIS_PATTERN_L_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

/**
 * @class Pattern_L
 * @brief Represents the L-shaped Tetris piece.
 *
 * This class inherits from CubePattern and implements the
 * logic for rotation, color, and wall kick offsets specific to the L-piece.
 */
class Pattern_L : public CubePattern {
public:
    /**
     * @brief Constructs the L-pattern with defined rotations and pivot.
     */
    Pattern_L();

    /**
     * @brief Returns the kick offsets used for rotation transitions.
     */
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;

    /**
     * @brief Returns the visual color for the L piece.
     */
    sf::Color getColor() const override;
};

#endif
