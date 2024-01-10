#include "board.h";
#include <queue>;
#include <unordered_set>
using namespace twixt;

Board::Board()  {
	m_board.resize(BOARD_SIZE);
	for (std::size_t i = 0; i < BOARD_SIZE; i++)
		m_board[i].resize(BOARD_SIZE);
};


Board::~Board() {
	for (size_t i = 0; i < BOARD_SIZE; i++)
		for (size_t j = 0; j < BOARD_SIZE; j++) {
			Cell& cell = m_board[i][j];
			if (cell.hasLinks())
				for (Link* link : cell.getLinks()) {
					Position pos1 = link->getP1().getPosition();
					Position pos2 = link->getP2().getPosition();
					if (isInBounds(pos1) && isInBounds(pos2)) {
						m_board[pos1.first][pos1.second].removeLink(link);
						m_board[pos2.first][pos2.second].removeLink(link);
					}
					delete link;
					link = nullptr;
				}

			if (cell.hasPeg()) {
				Peg* peg = &cell.getPeg();
				delete peg;
				peg = nullptr;
			}
		}
	std::cout << "test";
}

twixt::Board::Board(const Board& board)
{
	m_board.resize(BOARD_SIZE);
	for (std::size_t i = 0; i < BOARD_SIZE; i++)
		m_board[i].resize(BOARD_SIZE);

	for (size_t i = 0; i < BOARD_SIZE; i++)
		for (size_t j = 0; j < BOARD_SIZE; j++) {
			if (board[{i, j}].hasPeg()) {
				Peg* newPeg = new Peg(board[{i, j}].getPeg());
				m_board[i][j].setPeg(newPeg);
			}
		}
	
	for (size_t i = 0; i < BOARD_SIZE; i++)
		for (size_t j = 0; j < BOARD_SIZE; j++) {
			if (board[{i, j}].hasLinks()) {
				for (Link* link : board[{i, j}].getLinks()) {
					Position pos1 = link->getP1().getPosition();
					Position pos2 = link->getP2().getPosition();
					Peg& peg1 = m_board[pos1.first][pos1.second].getPeg();
					Peg& peg2 = m_board[pos2.first][pos2.second].getPeg();
					Link* newLink = new Link(peg1, peg2, peg1.getColor(), peg1.getQColor());
					m_board[i][j].addLink(newLink);
				}
			}
		}
	
}

void twixt::Board::drawBoard()
{
	for (size_t i = 0; i < BOARD_SIZE; i++) {
		for (size_t j = 0; j < BOARD_SIZE; j++) {
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

