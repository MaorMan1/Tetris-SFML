#ifndef TETRIS_BOARD_HPP
#define TETRIS_BOARD_HPP	
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.hpp"
#include <set>

using namespace std;

class CubePattern;

// Represents the main game board and its state
class Board {
private:
    char m_grid[HEIGHT][WIDTH] = {};              // Grid layout of the board ('_' means empty)
    sf::RectangleShape m_blockShape;              // Shape for rendering a single block
    float m_blockSize;                            // Calculated block size based on window
    sf::Vector2f m_boardOffset;                   // Offset from top-left corner

public:
    Board(sf::Vector2u windowSize);

    void draw(sf::RenderWindow& window, int alpha = 255); // Draw board with optional transparency
    std::set<int> lockPiece(const CubePattern& piece);    // Lock a falling piece into the grid
    bool checkCollision(const std::vector<sf::Vector2i>& positions); // Check if piece collides
    char getCell(int row, int col) const;                 // Get the value of a grid cell
    void updateBlockSize(sf::Vector2u windowSize);        // Recalculate block size and offset
    float getBlockSize() const;                           // Return block size
    sf::Vector2f getOffset() const;                       // Return board offset

    std::set<int> findFullLines(const std::set<int>& rowsToCheck) const; // Detect full rows
    void collapseLines(const std::set<int>& clearedRows); // Collapse lines after clearing
    void clearLinesFromGrid(const std::set<int>& fullLines); // Clear specific rows
    void clear();                                          // Clear entire board

    void debugPrint() const;                              // Print the board to console for debugging
};


#endif