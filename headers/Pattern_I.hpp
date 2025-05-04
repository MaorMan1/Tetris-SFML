#ifndef TETRIS_PATTERN_I_HPP
#define TETRIS_PATTERN_I_HPP
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "CubePattern.hpp"
#include "GamePlayPage.hpp"

class Pattern_I : public CubePattern {
public:
	Pattern_I();
	const std::vector<sf::Vector2i>& Pattern_I::getKickOffsets(int rotationIndex) const override;
	sf::Color Pattern_I::getColor() const;

private:
};

#endif 