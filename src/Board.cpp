#include "Board.hpp"
#include "CubePattern.hpp" 

Board::Board(sf::Vector2u windowSize)
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			m_grid[i][j] = '_';
		}
	}

	// Compute block size dynamically
	updateBlockSize(windowSize);
}

void Board::draw(sf::RenderWindow& window)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (m_grid[y][x] != '_') {  // Draw only filled cells
				sf::Vector2f pos;
				pos.x = m_boardOffset.x + x * m_blockSize;
				pos.y = m_boardOffset.y + y * m_blockSize;
				m_blockShape.setPosition(pos);

				// Set colors based on Tetrimino type
				switch (m_grid[y][x]) {
				case 'I': m_blockShape.setFillColor(sf::Color::Cyan); break;
				case 'O': m_blockShape.setFillColor(sf::Color::Yellow); break;
				case 'T': m_blockShape.setFillColor(sf::Color::Magenta); break;
				case 'S': m_blockShape.setFillColor(sf::Color::Green); break;
				case 'Z': m_blockShape.setFillColor(sf::Color::Red); break;
				case 'J': m_blockShape.setFillColor(sf::Color::Blue); break;
				case 'L': m_blockShape.setFillColor(sf::Color::White); break;
				default: m_blockShape.setFillColor(sf::Color::Black); break;
				}

				window.draw(m_blockShape);
			}
		}
	}
}

std::set<int> Board::lockPiece(const CubePattern& piece)
{
	std::set<int> affectedRows;

	auto currPos = piece.getPivot();
	for (const auto& block : piece.getPatternPositions(currPos)) {
		int row = block.y;
		int col = block.x;
		if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
			m_grid[row][col] = piece.getPatternGridSign();  // Different letters per piece
			affectedRows.insert(row);
		}
	}
	return affectedRows;
}

bool Board::checkCollision(const std::vector<sf::Vector2i>& positions)
{
	for (const auto& pos : positions) {
		int row = pos.y,
			col = pos.x;
		if (col < 0 || col >= WIDTH || /*row < 0 || */row >= HEIGHT)
			return true;
		if (row >= 0 && m_grid[row][col] != '_') // If occupied cell and the first specific edge case is for spawn + rotate  
			return true;
	}
	return false;
}

char Board::getCell(int row, int col) const
{
	return m_grid[row][col];
}

void Board::updateBlockSize(sf::Vector2u windowSize) {
	float boardWidth = windowSize.x - UI_WIDTH;  // Leave space for UI on the right
	float boardHeight = windowSize.y;            // Use full height

	m_blockSize = std::min(boardWidth / WIDTH, boardHeight / HEIGHT); // Scale blocks to fit

	m_boardOffset = sf::Vector2f(0, 0);  // Board starts at (0,0), UI is on the right

	m_blockShape.setSize(sf::Vector2f(m_blockSize, m_blockSize));
	m_blockShape.setOutlineThickness(1);
	m_blockShape.setOutlineColor(sf::Color::Black);
}

float Board::getBlockSize() const
{
	return m_blockSize;
}

std::set<int> Board::findFullLines(const std::set<int>& rowsToCheck) const
{
	std::set<int> fullLines;
	for (int row : rowsToCheck) {
		bool full = true;
		for (int col = 0; col < WIDTH; ++col) {
			if (m_grid[row][col] == '_') { // If not full
				full = false;
				break;
			}
		}
		if (full) {
			fullLines.insert(row);
		}
	}
	return fullLines;
}

//void Board::clearLines(const std::set<int>& fullLines)
//{
//	for (int row : fullLines) {
//		for (int y = row; y > 0; --y) {
//			for (int x = 0; x < WIDTH; ++x) {
//				m_grid[y][x] = m_grid[y - 1][x];
//			}
//		}
//
//		// Clear top row
//		for (int x = 0; x < WIDTH; ++x) {
//			m_grid[0][x] = '_';
//		}
//	}
//}

sf::Vector2f Board::getOffset() const
{
	return m_boardOffset;
}

void Board::collapseLines(const std::set<int>& clearedRows)
{
	if (clearedRows.empty())
		return;

	int shift = 0;	// For better time complexity if more then one row cleared

	for (int row = HEIGHT - 1; row >= 0; --row)
	{
		if (clearedRows.count(row))
		{
			shift++; // this row was cleared, so increase shift
		}
		else if (shift > 0)
		{
			// move this row downward by 'shift' rows
			for (int col = 0; col < WIDTH; ++col)
			{
				m_grid[row + shift][col] = m_grid[row][col];
				m_grid[row][col] = '_'; // empty old row
			}
		}
	}
}

void Board::clearLinesFromGrid(const std::set<int>& fullLines)
{
	for (int row : fullLines) {
		for (int col = 0; col < WIDTH; ++col) {
			m_grid[row][col] = '_';
		}
	}
}


void Board::debugPrint() const
{
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			std::cout << m_grid[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << "======================" << std::endl;
}
