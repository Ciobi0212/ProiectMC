#pragma once

#include <iostream> 
#include <vector>

#include "Cell.h" 

namespace twixt {

    class Board {
    public:
        // Constructors and destructor
        Board(size_t boardSize = 12);
        ~Board();
        Board(const Board& board);

        // Getter for board size
        size_t getSize() const;

        // Utility functions
        bool isInBounds(const Position<>& pos) const;
        void cleanLink(Link* link);
        void cleanCell(Cell& cell);
        void cleanPeg(Peg& peg);
        void resetBoard();

        // Operator overloads
        Cell& operator[](const Position<>& pos);
        const Cell& operator[](const Position<>& pos) const;

    private:
        // Member variables
        std::vector<std::vector<Cell>> m_board;
        size_t BOARD_SIZE;
    };
}
