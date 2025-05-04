#include "CubePattern.hpp"
#include "Board.hpp"

void CubePattern::moveLeft(Board& board) {
    sf::Vector2i nextStep(m_pivot.x - 1, m_pivot.y);
    auto nextPatternPos = this->getPatternPositions(nextStep);
    if (!board.checkCollision(nextPatternPos)) {
        m_pivot.x--;  // Move left in the grid
    }
}

void CubePattern::moveRight(Board& board) {
    sf::Vector2i nextStep(m_pivot.x + 1, m_pivot.y);
    auto nextPatternPos = this->getPatternPositions(nextStep);/*
    for (auto x : nextPatternPos) {
        cout << x.y << " " << x.x << endl;
    }*/
    if (!board.checkCollision(nextPatternPos)) {
        m_pivot.x++;  // Move right in the grid
    }
}

void CubePattern::moveDown(Board& board) {
    sf::Vector2i nextStep(m_pivot.x, m_pivot.y + 1);
    auto nextPatternPos = this->getPatternPositions(nextStep);
    if (!board.checkCollision(nextPatternPos)) {
        m_pivot.y++;  // Move down in the grid
    }
}

std::vector<sf::Vector2i> CubePattern::getPatternPositions(const sf::Vector2i nextPivot, const bool rotate) const
{
    vector<sf::Vector2i> nextPatternPos;
    int ind = (m_rotationIndex + 1) % m_rotations.size();
    for (const auto& r : m_rotations[(rotate) ? ind : m_rotationIndex]) {
        sf::Vector2i nextCurrPiv;
        nextCurrPiv.x = r.x + nextPivot.x;
        nextCurrPiv.y = r.y + nextPivot.y;
        nextPatternPos.push_back(nextCurrPiv);
    }
    return nextPatternPos;
}

void CubePattern::rotate(Board& board) {
    int nextRotation = (m_rotationIndex + 1) % m_rotations.size();
    const auto& kicks = getKickOffsets(m_rotationIndex);  // Rotation dependent!

    for (const auto& offset : kicks) {
        sf::Vector2i testPivot = m_pivot + offset;
        auto rotated = getPatternPositions(testPivot, true);
        if (!board.checkCollision(rotated)) {
            m_pivot = testPivot;
            m_rotationIndex = nextRotation;
            return;
        }
    }
    // If no kick works, no rotation
}

void CubePattern::draw(sf::RenderWindow& window, Board& board)
{
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(board.getBlockSize(), board.getBlockSize()));
    block.setOutlineThickness(1);
    block.setOutlineColor(sf::Color::Black);
    block.setFillColor(getColor());

    for (const auto& offset : m_rotations[m_rotationIndex]) {
        sf::Vector2i absPos = m_pivot + offset;
        sf::Vector2f pixelPos = board.getOffset() + sf::Vector2f(absPos.x, absPos.y) * board.getBlockSize();

        block.setPosition(pixelPos);
        window.draw(block);
    }
}

sf::Vector2i CubePattern::getPivot() const
{
    return m_pivot;
}

char CubePattern::getPatternGridSign() const
{
    return m_gridSign;
}
