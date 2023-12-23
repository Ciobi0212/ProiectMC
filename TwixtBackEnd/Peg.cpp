#include "Peg.h"
using namespace twixt;

Peg::Peg() = default;

Peg::Peg(size_t rowOnBoard, size_t columnOnBoard, Color color) : m_rowOnBoard{ rowOnBoard }, m_columnOnBoard{ columnOnBoard }, m_color{ color } {}

Peg::~Peg() = default;

size_t Peg::getRowOnBoard() const {
    return m_rowOnBoard;
}

size_t Peg::getColumnOnBoard() const {
    return m_columnOnBoard;
}

Color Peg::getColor() const {
    return m_color;
}

void Peg::setRowOnBoard(uint16_t rowOnBoard) {
    m_rowOnBoard = rowOnBoard;
}

void Peg::setColumnOnBoard(uint16_t columnOnBoard) {
    m_columnOnBoard = columnOnBoard;
}

void Peg::setColor(Color color) {
    m_color = color;
}

bool Peg::operator==(const Peg& peg) const {
    return m_rowOnBoard == peg.m_rowOnBoard && m_columnOnBoard == peg.m_columnOnBoard;
}

Position Peg::getPosition() const {
    return Position{ m_rowOnBoard, m_columnOnBoard };
}