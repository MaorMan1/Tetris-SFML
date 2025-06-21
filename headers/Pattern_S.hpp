#ifndef TETRIS_PATTERN_S_HPP
#define TETRIS_PATTERN_S_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

/**
 * @class Pattern_S
 * @brief Represents the S-shaped Tetris piece.
 *
 * This class defines the two rotation states of the S-piece,
 * its pivot point, and kick behavior.
 */
class Pattern_S : public CubePattern {
public:
    /**
     * @brief Constructs the S pattern with default rotation and pivot.
     */
    Pattern_S();

    /**
     * @brief Returns the wall kick offsets for rotation transitions.
     */
    const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const override;

    /**
     * @brief Returns the color used for the S-piece (Green).
     */
    sf::Color getColor() const override;
};

#endif
