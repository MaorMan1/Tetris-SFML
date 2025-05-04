#include "Pattern_I.hpp"

Pattern_I::Pattern_I()
{
    m_pivot = sf::Vector2i(WIDTH / 2 - 1, 0);
    m_gridSign = 'I';
    m_rotations = {
        { {-1, 0}, {0, 0}, {1, 0}, {2, 0} },  // Horizontal
        { {0, -1}, {0, 0}, {0, 1}, {0, 2} }   // Vertical
    };
}

const std::vector<sf::Vector2i>& Pattern_I::getKickOffsets(int rotationIndex) const {
    static const std::vector<std::vector<sf::Vector2i>> kicksPerRotation = {
            { {0, 0}, {0, -1}, {0, -2} }, // from rotation 0
            { {0, 0}, {1, 0}, {-1, 0}, {-2, 0} }, // from rotation 1
    };
    return kicksPerRotation[rotationIndex % kicksPerRotation.size()];
}

sf::Color Pattern_I::getColor() const
{
    return sf::Color::Cyan;
}
