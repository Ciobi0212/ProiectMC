export module board;

import <iostream>;
import <vector>;

import peg;
using twixt::Peg;

import link;
using twixt::Link;



namespace twixt {
    enum class cellState {
		EMPTY, RED, BLUE
	};

	export class Board {
	public: 
		Board();
		~Board();


		
		
	private:
		const uint16_t BOARD_SIZE{24};
		std::vector<std::vector<cellState>> board;
		
		
	};
}