#include "Pattern_S.hpp"

Pattern_S::Pattern_S()
{
    m_pivot = sf::Vector2i(WIDTH / 2 - 1, 0);
    m_gridSign = 'S';

    m_rotations = {
        { {0, 0}, {1, 0}, {-1, 1}, {0, 1} },   // Horizontal (default)
        { {0, 0}, {0, -1}, {1, 0}, {1, 1} }    // Vertical
    };
}

const std::vector<sf::Vector2i>& Pattern_S::getKickOffsets(int rotationIndex) const {
    static const std::vector<std::vector<sf::Vector2i>> kicksPerRotation = {
        { {0, 0}, {0, -1}, {0, 1}, {0, 2} },  // from horizontal to vertical
        { {0, 0}, {1, 0}, {2, 0} }      // from vertical to horizontal
    };
    return kicksPerRotation[rotationIndex % kicksPerRotation.size()];
}

sf::Color Pattern_S::getColor() const
{
    return sf::Color::Green;
}
