#include "qtPeg.h";
using namespace twixt;

qtPeg::qtPeg() = default;

qtPeg::qtPeg(size_t rowOnBoard, size_t columnOnBoard, Color color, QPoint positionOnScreen, QColor qcolor) : m_rowOnBoard{ rowOnBoard }, m_columnOnBoard{ columnOnBoard }, m_color{ color }, m_positionOnScreen{ positionOnScreen }, m_qcolor{qcolor} {}

qtPeg::~qtPeg() = default;

size_t qtPeg::getRowOnBoard() const {
	return m_rowOnBoard;
}

size_t qtPeg::getColumnOnBoard() const {
	return m_columnOnBoard;
}

Color qtPeg::getColor() const {
	return m_color;
}

void qtPeg::setRowOnBoard(uint16_t rowOnBoard) {
	m_rowOnBoard = rowOnBoard;
}

void qtPeg::setColumnOnBoard(uint16_t columnOnBoard) {
	m_columnOnBoard = columnOnBoard;
}

void qtPeg::setColor(Color color) {
	m_color = color;
}

bool qtPeg::operator==(const qtPeg& peg) const {
	return m_rowOnBoard == peg.m_rowOnBoard && m_columnOnBoard == peg.m_columnOnBoard;
}

Position qtPeg::getPosition() const {
	return Position{ m_rowOnBoard, m_columnOnBoard };
}

QPoint twixt::qtPeg::getPositionOnScreen() const
{
	return m_positionOnScreen;
}

QColor twixt::qtPeg::getQColor() const
{
	return m_qcolor;
}

void twixt::qtPeg::setPositionOnScreen(QPoint positionOnScreen)
{
	m_positionOnScreen = positionOnScreen;
}

void twixt::qtPeg::setQColor(QColor qcolor)
{
	m_qcolor = qcolor;
}





