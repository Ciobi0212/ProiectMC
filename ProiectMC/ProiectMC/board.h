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
		uint16_t getSize() const;
		
		using Position = std::pair<uint8_t, uint8_t>;

		bool isInBounds(const Position& pos) const;

		Cell& operator[](const Position& pos);
		const Cell& operator[](const Position& pos) const;
		

	private:
		static const uint16_t BOARD_SIZE{ 24 };
		std::vector<std::vector<Cell>> board;
	};
}