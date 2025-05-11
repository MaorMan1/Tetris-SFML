#ifndef TETRIS_CUBEPATTERN_HPP
#define TETRIS_CUBEPATTERN_HPP
#include <SFML/Graphics.hpp>

class Board;

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
	void draw(sf::RenderWindow& window, Board& board);
	sf::Vector2i getPivot() const;
	char getPatternGridSign() const;


	// Check
	void drawGhost(sf::RenderWindow& window, const Board& board, const sf::Vector2i& ghostPivot) const;

};


#endif