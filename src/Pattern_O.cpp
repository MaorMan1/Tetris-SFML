#include "Pattern_O.hpp"

Pattern_O::Pattern_O()
{
    m_pivot = sf::Vector2i(WIDTH / 2 - 1, 1); // Start near the top-middle
    m_gridSign = 'O';

    // Only one rotation state for 'O'
    m_rotations = {
        { {0, -1}, {0, 0}, {1, 0}, {1, -1} }
    };
}

const std::vector<sf::Vector2i>& Pattern_O::getKickOffsets(int rotationIndex) const {
    static const std::vector<std::vector<sf::Vector2i>> kicksPerRotation = {
        { {0, 0} }  // From rotation 0
    };
    return kicksPerRotation[rotationIndex % kicksPerRotation.size()];
}

sf::Color Pattern_O::getColor() const
{
    return sf::Color::Yellow;
}