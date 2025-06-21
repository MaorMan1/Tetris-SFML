#ifndef TETRIS_PATTERN_T_HPP
#define TETRIS_PATTERN_T_HPP
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

/**
 * @class Pattern_T
 * @brief Represents the T-shaped Tetris piece.
 *
 * Defines four rotation states and wall kick offsets for the T tetromino.
 */
class Pattern_T : public CubePattern {
public:
    /**
     * @brief Constructs the T pattern with defined rotations and pivot.
     */
    Pattern_T();

    /**
     * @brief Returns wall kick offsets for the given rotation index.
     */
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;

    /**
     * @brief Returns the color of the T pattern (Magenta).
     */
    sf::Color getColor() const override;
};

#endif 