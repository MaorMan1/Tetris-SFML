#ifndef TETRIS_CUBEPATTERN_HPP
#define TETRIS_CUBEPATTERN_HPP

#include <SFML/Graphics.hpp>
#include "UIBar.hpp"

// Forward declarations
class Board;
class DisplayWindow;

/*
 * Abstract base class for all Tetris pattern shapes (I, O, T, etc.)
 * Handles movement, rotation, rendering, and ghost preview.
 */
class CubePattern {
protected:
	sf::Vector2i m_pivot; // Position of the pattern's center block
	char m_gridSign;      // Character representing the pattern on the board grid
	std::vector<std::vector<sf::Vector2i>> m_rotations; // All rotational states
	int m_rotationIndex = 0; // Current rotation state

public:
    virtual ~CubePattern() = default;

    // Movement logic
    void moveRight(Board& board);
    void moveLeft(Board& board);
    void moveDown(Board& board);

    // Rotation logic with wall kick system
    void rotate(Board& board);
    virtual const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const = 0;

    // Position & grid logic
    std::vector<sf::Vector2i> getPatternPositions(const sf::Vector2i nextPivot, bool rotate = false) const;
    sf::Vector2i getPivot() const;
    char getPatternGridSign() const;

    // Drawing logic
    void draw(sf::RenderWindow& window, Board& board, int alpha = 255);
    void drawGhost(sf::RenderWindow& window, const Board& board, const sf::Vector2i& ghostPivot) const;
    void drawDisplayPattern(sf::RenderWindow& window, float blockSize, const DisplayWindow& display, int alpha) const;

    // Color definitions
    virtual sf::Color getColor() const = 0;
    sf::Color getGhostColor() const;
};


#endif