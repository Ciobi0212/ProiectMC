#pragma once

#include <iostream>;
#include <vector>;
#include "cell.h"

namespace twixt {
	 class Board {
	public:
		Board();
		~Board();
		Board(const Board& board);

		size_t getSize() const;

	    bool isInBounds(const Position& pos) const;
		void cleanLink(Link* link);
		void cleanCell(Cell& cell);
		void cleanPeg(Peg& peg);
		void resetBoard();

		Cell& operator[](const Position& pos);
		const Cell& operator[](const Position& pos) const;
		

	public:
		static constexpr size_t BOARD_SIZE{ 12 };
		
	 private:
		std::vector<std::vector<Cell>> m_board;
	};
}