#pragma once
#include <vector>
#include <utility>
#include <unordered_set>
#include "Cell.h"

namespace twixt {
	class __declspec(dllexport) Board {
	public:
		Board(size_t BOARD_SIZE = 24);
		~Board();

		void drawBoard();
		size_t getSize() const;

		using Position = std::pair<std::size_t, std::size_t>;
		struct PositionHash {
			std::size_t operator()(const Position& pos) const {
				return std::hash<std::size_t>()(pos.first) ^ std::hash<std::size_t>()(pos.second);
			}
		};

		bool isInBounds(const Position& pos) const;

		Cell& operator[](const Position& pos);
		const Cell& operator[](const Position& pos) const;

	private:
		std::vector<std::vector<Cell>> m_board;
		size_t BOARD_SIZE;
	};
}

