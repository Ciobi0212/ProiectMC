#include "board.h";

using namespace twixt;

Board::Board()  {
	m_board.resize(BOARD_SIZE);
	for (std::size_t i = 0; i < BOARD_SIZE; i++)
		m_board[i].resize(BOARD_SIZE);
};


Board::~Board() = default;

void twixt::Board::drawBoard()
{
	for (uint8_t i = 0; i < BOARD_SIZE; i++) {
		for (uint8_t j = 0; j < BOARD_SIZE; j++) {
			Cell& curentCell = m_board[i][j];
				Color color = curentCell.getColor();
				switch (color) {
				case Color::RED:
					std::cout << "R";
					break;
				case Color::BLUE:
					std::cout << "B";
					break;
				default:
					std::cout << " ";
					break;
				}
		}
		std::cout << std::endl;
	}
}

size_t twixt::Board::getSize() const
{
	return BOARD_SIZE;
}

bool twixt::Board::isInBounds(const Position& pos) const
{
	auto& [line, column] = pos;

	return line >= 0 && line < BOARD_SIZE&& column >= 0 && column < BOARD_SIZE;
}

Cell& twixt::Board::operator[](const Position& pos)
{
	auto& [line, column] = pos;

	if (!isInBounds(pos))
		throw std::out_of_range("Position out of bounds");

	return m_board[line][column];
	
}

const Cell& twixt::Board::operator[](const Position& pos) const
{
	auto& [line, column] = pos;

	if (!isInBounds(pos))
		throw std::out_of_range("Position out of bounds");

	return m_board[line][column];
}

