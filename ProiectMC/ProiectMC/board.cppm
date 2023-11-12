export module board;

import <iostream>;
import <vector>;

import peg;
using twixt::Peg;

import link;
using twixt::Link;

namespace twixt {
	export class Board {
	public: 


		
		
	private:
		const uint16_t BOARD_SIZE{24};
		std::vector<Peg> pegs;
		std::vector<Link> links;
	};
}