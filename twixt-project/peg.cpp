#include "peg.h";
using namespace twixt;

Peg::Peg() = default;

Peg::Peg(size_t rowOnBoard, size_t columnOnBoard, Color color, QPoint positionOnScreen, QColor qcolor) : m_rowOnBoard{ rowOnBoard }, m_columnOnBoard{ columnOnBoard }, m_color{ color }, m_positionOnScreen{ positionOnScreen }, m_qcolor{qcolor} {}

twixt::Peg::Peg(const Peg& peg)
{
	m_rowOnBoard = peg.m_rowOnBoard;
	m_columnOnBoard = peg.m_columnOnBoard;
	m_color = peg.m_color;
	m_positionOnScreen = peg.m_positionOnScreen;
	m_qcolor = peg.m_qcolor;
}

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

Position<> Peg::getPosition() const {
	return Position{ m_rowOnBoard, m_columnOnBoard };
}

QPoint twixt::Peg::getPositionOnScreen() const
{
	return m_positionOnScreen;
}

QColor twixt::Peg::getQColor() const
{
	return m_qcolor;
}

void twixt::Peg::setPositionOnScreen(QPoint positionOnScreen)
{
	m_positionOnScreen = positionOnScreen;
}

void twixt::Peg::setQColor(QColor qcolor)
{
	m_qcolor = qcolor;
}





