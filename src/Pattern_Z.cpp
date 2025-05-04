#include "Pattern_Z.hpp"

Pattern_Z::Pattern_Z()
{
    m_pivot = sf::Vector2i(WIDTH / 2 - 1, 0);
    m_gridSign = 'Z';

    m_rotations = {
        { {0, 0}, {-1, 0}, {0, 1}, {1, 1} },   // Horizontal
        { {0, 0}, {0, -1}, {-1, 0}, {-1, 1} }  // Vertical
    };
}

const std::vector<sf::Vector2i>& Pattern_Z::getKickOffsets(int rotationIndex) const {
    static const std::vector<std::vector<sf::Vector2i>> kicksPerRotation = {
        { {0, 0}, {1, 0}, {0, 1} },  // from horizontal to vertical
        { {0, 0}, {-1, 0}, {-2, 0} }      // from vertical to horizontal
    };
    return kicksPerRotation[rotationIndex % kicksPerRotation.size()];
}

sf::Color Pattern_Z::getColor() const
{
    return sf::Color::Red;
}
