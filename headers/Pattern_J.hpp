#ifndef TETRIS_PATTERN_J_HPP 
#define TETRIS_PATTERN_J_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"

class Pattern_J : public CubePattern { 
public: 
	Pattern_J(); 
	const std::vector<sf::Vector2i>& Pattern_J::getKickOffsets(int rotationIndex) const override;
	sf::Color getColor() const override; 
}; 
#endif