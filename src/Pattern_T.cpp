#include "Pattern_T.hpp"

Pattern_T::Pattern_T()
{
    m_pivot = sf::Vector2i(WIDTH / 2 - 1, 0); // Start near the top-middle
    m_gridSign = 'T';

    m_rotations = {
    // Define T
    { {-1, 0}, {0, 0}, {1, 0}, {0, 1} },

    // Define T - 90 degree clockwise
    { {0, -1}, {0, 0}, {0, 1}, {-1, 0} },

    // Define T - 180 degree clockwise
    { {-1, 0}, {0, 0}, {1, 0}, {0, -1} },

    // Define T - 270 degree clockwise
    { {0, -1}, {0, 0}, {0, 1}, {1, 0} }
    };
}

const std::vector<sf::Vector2i>& Pattern_T::getKickOffsets(int rotationIndex) const
{
    static const std::vector<std::vector<sf::Vector2i>> kicksPerRotation = {
        { {0, 0}, {0, 1} }, // from rotation 0
        { {0, 0}, {-1, 0} }, // from rotation 1
        { {0, 0}, {0, -1} }, // from rotation 2
        { {0, 0}, {1, 0} } // from rotation 3
    };
    return kicksPerRotation[rotationIndex % kicksPerRotation.size()];
}

sf::Color Pattern_T::getColor() const
{
    return sf::Color::Magenta;
}