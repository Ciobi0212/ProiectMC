#include "board.h";

using twixt::Board;
using twixt::Cell;

Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::vector<Cell> row;
		for (int j = 0; j < BOARD_SIZE; j++) {
			row.push_back(Cell());
		}
		board.push_back(row);
	}
}

Board::~Board() = default;

void twixt::Board::drawBoard()
{
	for (uint8_t i = 0; i < BOARD_SIZE; i++) {
		for (uint8_t j = 0; j < BOARD_SIZE; j++) {
			Cell& curentCell = board[i][j];
			if (curentCell.hasPeg()) {
				std::cout << curentCell.getPeg().getColor()<<" ";
			}
			else {
				std::cout << "E ";
			}
		}
		std::cout << std::endl;
	}
}

uint16_t twixt::Board::getSize() const
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

	if (line < 0 || line > BOARD_SIZE || column < 0 || column > BOARD_SIZE)
		throw std::out_of_range("Position out of bounds");

	return board[line][column];
	
}

const Cell& twixt::Board::operator[](const Position& pos) const
{
	auto& [line, column] = pos;

	if (line < 0 || line > BOARD_SIZE || column < 0 || column > BOARD_SIZE)
		throw std::out_of_range("Position out of bounds");

	return board[line][column];
}

