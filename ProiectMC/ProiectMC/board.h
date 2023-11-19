#pragma once
export module board;

#include <iostream>;
#include <vector>;

#include "cell.h"

namespace twixt {

	export class Board {
	public:
		Board();
		~Board();

	private:
		const uint16_t BOARD_SIZE{ 24 };
		std::vector<std::vector<Cell>> board;


	};
}