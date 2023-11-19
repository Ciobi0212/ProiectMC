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

