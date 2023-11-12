module board;
using twixt::Board;
import <iostream>;
import <vector>;

import peg;
using twixt::Peg;

import link;
using twixt::Link;


Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		std::vector<cellState> row;
		for (int j = 0; j < BOARD_SIZE; j++) {
			row.push_back(cellState::EMPTY);
		}
		board.push_back(row);
	}
}

Board::~Board() = default;