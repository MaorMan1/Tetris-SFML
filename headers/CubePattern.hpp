#ifndef TETRIS_CUBEPATTERN_HPP
#define TETRIS_CUBEPATTERN_HPP
#include <SFML/Graphics.hpp>
#include "UIBar.hpp"

class Board;
class DisplayWindow;

class CubePattern {
protected:
	sf::Vector2i m_pivot; // Base pattern location
	char m_gridSign;
	std::vector<std::vector<sf::Vector2i>> m_rotations; // All rotations state
	int m_rotationIndex = 0;

public:
	void moveRight(Board& board);
	void moveLeft(Board& board);
	void moveDown(Board& board);
	//checking
	virtual const std::vector<sf::Vector2i>& getKickOffsets(int rotationIndex) const = 0;
	std::vector<sf::Vector2i> getPatternPositions(const sf::Vector2i nextPivot, const bool rotate = false) const;
	void rotate(Board& board);
	virtual sf::Color getColor() const = 0;
	sf::Color getGhostColor() const;
	void draw(sf::RenderWindow& window, Board& board, const int alpha = 255);
	sf::Vector2i getPivot() const;
	char getPatternGridSign() const;
	void drawGhost(sf::RenderWindow& window, const Board& board, const sf::Vector2i& ghostPivot) const;
	void drawDisplayPattern(sf::RenderWindow& window, const float blockSize, const DisplayWindow& display, const int alpha) const;
};


#endif