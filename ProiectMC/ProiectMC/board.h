#pragma once

#include <iostream>;
#include <vector>;

#include "cell.h"

namespace twixt {

	 class Board {
	public:
		Board();
		~Board();
		
		void drawBoard();
		size_t getSize() const;
		
		using Position = std::pair<uint8_t, uint8_t>;

	    bool isInBounds(const Position& pos) const;

		Cell& operator[](const Position& pos);
		const Cell& operator[](const Position& pos) const;
		

	private:
		static const size_t BOARD_SIZE{ 8 };
		std::vector<std::vector<Cell>> m_board;
	};
}