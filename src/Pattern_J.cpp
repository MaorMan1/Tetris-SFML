#include "Pattern_J.hpp"

Pattern_J::Pattern_J()
{
    m_pivot = sf::Vector2i(WIDTH / 2 - 1, 0);
    m_gridSign = 'J';
    m_rotations = {
        { {-1, 0}, {0, 0}, {1, 0}, {1, 1} },
        { {0, -1}, {0, 0}, {0, 1}, {-1, 1} },
        { {-1, -1}, {-1, 0}, {0, 0}, {1, 0} },
        { {0, -1}, {0, 0}, {0, 1}, {1, -1} }
    };
}

const std::vector<sf::Vector2i>& Pattern_J::getKickOffsets(int rotationIndex) const {
    static const std::vector<std::vector<sf::Vector2i>> kicksPerRotation = {
        { {0, 0}, {0, 1}, {1, 0}, {2, 0} }, // from rotation 0
        { {0, 0}, {-1, 0}, {0, 1}, {0, 2} }, // from rotation 1
        { {0, 0}, {-1, 0}, {-2, 0}, {0, -1} }, // from rotation 2
        { {0, 0}, {1, 0}, {0, -1}, {0, -2} } // from rotation 3
    };
    return kicksPerRotation[rotationIndex % kicksPerRotation.size()];
}

sf::Color Pattern_J::getColor() const
{
    return sf::Color::Blue;
}