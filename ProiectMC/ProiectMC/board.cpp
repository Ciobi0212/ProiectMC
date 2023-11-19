#include "board.h";
using twixt::Board;

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

