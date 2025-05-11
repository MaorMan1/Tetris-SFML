#ifndef TETRIS_BOARD_HPP
#define TETRIS_BOARD_HPP	
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.hpp"
#include <set>

using namespace std;

class CubePattern;

class Board {
private:
    char m_grid[HEIGHT][WIDTH] = {}; 
    sf::RectangleShape m_blockShape;  
    float m_blockSize; 
    sf::Vector2f m_boardOffset;

public:
    Board(sf::Vector2u windowSize); 
    void draw(sf::RenderWindow& window, const int alpha = 255);
    std::set<int> lockPiece(const CubePattern& piece);
    bool checkCollision(const std::vector<sf::Vector2i>& positions);
    char getCell(int x, int y) const;
    void updateBlockSize(sf::Vector2u windowSize);
    float getBlockSize() const;
    std::set<int> findFullLines(const std::set<int>& rowsToCheck) const;
    //void clearLines(const std::set<int>& fullLines);
    void collapseLines(const std::set<int>& clearedRows);
    void clearLinesFromGrid(const std::set<int>& fullLines);
    sf::Vector2f getOffset() const;
    void clear();
    //check
    void debugPrint() const;
};


#endif