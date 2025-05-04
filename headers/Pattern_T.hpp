#ifndef TETRIS_PATTERN_T_HPP
#define TETRIS_PATTERN_T_HPP
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

class Pattern_T : public CubePattern {
public:
	Pattern_T();
	const std::vector<sf::Vector2i>& Pattern_T::getKickOffsets(int rotationIndex) const override;
	sf::Color getColor() const override;

private:
};

#endif 