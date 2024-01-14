#include "board.h"
#include <iostream>

namespace twixt {

    Board::Board(size_t boardSize) : BOARD_SIZE{ boardSize } {
		m_board.resize(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE));
    }
   
    Board::~Board() {
        for (size_t i = 0; i < BOARD_SIZE; i++) {
            for (size_t j = 0; j < BOARD_SIZE; j++) {
                cleanCell(m_board[i][j]);
            }
        }
    }

    Board::Board(const Board& board) {
		BOARD_SIZE = board.getSize();
        m_board.resize(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE));

        for (size_t i = 0; i < BOARD_SIZE; i++) {
            for (size_t j = 0; j < BOARD_SIZE; j++) {
                if (board[{i, j}].hasPeg()) {
                    Peg* newPeg = new Peg(board[{i, j}].getPeg());
                    m_board[i][j].setPeg(newPeg);
					m_board[i][j].setColor(newPeg->getColor());
                }
            }
        }

        for (size_t i = 0; i < BOARD_SIZE; i++) {
            for (size_t j = 0; j < BOARD_SIZE; j++) {
                if (board[{i, j}].hasLinks()) {
                    for (Link* link : board[{i, j}].getLinks()) {
                        Position pos1 = link->getP1().getPosition();
                        Position pos2 = link->getP2().getPosition();
                        Peg& peg1 = m_board[pos1.first][pos1.second].getPeg();
                        Peg& peg2 = m_board[pos2.first][pos2.second].getPeg();
                        Link* newLink = new Link(peg1, peg2, peg1.getColor(), peg1.getQColor());
                        m_board[i][j].addLink(newLink);
						m_board[i][j].setColor(peg1.getColor());
                    }
                }
            }
        }
    }

    size_t Board::getSize() const {
        return BOARD_SIZE;
    }

    bool Board::isInBounds(const Position<>& pos) const {
        auto& [line, column] = pos;
        return line >= 0 && line < BOARD_SIZE && column >= 0 && column < BOARD_SIZE;
    }

    void Board::resetBoard() {
        m_board.clear();
        m_board.resize(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE));
    }

    Cell& Board::operator[](const Position<>& pos) {
        auto& [line, column] = pos;

        if (!isInBounds(pos)) {
            throw std::out_of_range("Position out of bounds");
        }

        return m_board[line][column];
    }

    const Cell& Board::operator[](const Position<>& pos) const {
        auto& [line, column] = pos;

        if (!isInBounds(pos)) {
            throw std::out_of_range("Position out of bounds");
        }

        return m_board[line][column];
    }

    void Board::cleanCell(Cell& cell) {
        if (cell.hasLinks()) {
			for (Link* link : cell.getLinks()) {
				cleanLink(link);
			}
        }

        if (cell.hasPeg()) {
            cleanPeg(cell.getPeg());
        }
    }

    void Board::cleanLink(Link* link) {
        Position pos1 = link->getP1().getPosition();
        Position pos2 = link->getP2().getPosition();
        if (isInBounds(pos1) && isInBounds(pos2)) {
            m_board[pos1.first][pos1.second].removeLink(link);
            m_board[pos2.first][pos2.second].removeLink(link);
        }

        delete link;
    }

    void Board::cleanPeg(Peg& peg) {
        delete& peg;
    }

}  
