#include "Pattern_L.hpp"

Pattern_L::Pattern_L()
{
    m_pivot = sf::Vector2i(WIDTH / 2 - 1, 0);
    m_gridSign = 'L';
    m_rotations = {
        { {-1, 0}, {0, 0}, {1, 0}, {-1, 1} },
        { {0, -1}, {0, 0}, {0, 1}, {-1, -1} },
        { {-1, 0}, {0, 0}, {1, 0}, {1, -1} },
        { {0, -1}, {0, 0}, {0, 1}, {1, 1} }
    };
}

const std::vector<sf::Vector2i>& Pattern_L::getKickOffsets(int rotationIndex) const {
    static const std::vector<std::vector<sf::Vector2i>> kicksPerRotation = {
        { {0, 0}, {0, 1}, {1, 0}, {-1, 0}, {0, -1}},   // from rotation 0
        { {0, 0}, {-1, 0}, {0, 1} },     // from rotation 1
        { {0, 0}, {0, -1}, {-1, 0} },    // from rotation 2
        { {0, 0}, {1, 0}, {0, -1} }   // from rotation 3
    };
    return kicksPerRotation[rotationIndex % kicksPerRotation.size()];
}

sf::Color Pattern_L::getColor() const
{
    return sf::Color::White;
}
