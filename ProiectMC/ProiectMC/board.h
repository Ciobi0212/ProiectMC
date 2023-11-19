#pragma once

#include <iostream>;
#include <vector>;

#include "cell.h"

namespace twixt {

	export class Board {
	public:
		Board();
		~Board();
		
		using Position = std::pair<uint8_t, uint8_t>;

		
		Cell& operator[](const Position& pos);
		const Cell& operator[](const Position& pos) const;
		

	private:
		static const uint16_t BOARD_SIZE{ 24 };
		std::vector<std::vector<Cell>> board;


	};
}