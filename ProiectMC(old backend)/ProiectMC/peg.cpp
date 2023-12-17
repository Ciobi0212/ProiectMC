#include "peg.h";
using namespace twixt;

Peg::Peg() = default;

Peg::Peg(size_t x, size_t y, Color color) : m_x{ x }, m_y{ y }, m_color{color} {}

Peg::~Peg() = default;

size_t Peg::getX() const {
	return m_x;
}

size_t Peg::getY() const {
	return m_y;
}

Color Peg::getColor() const {
	return m_color;
}

void Peg::setX(uint16_t x) {
	m_x = x;
}

void Peg::setY(uint16_t y) {
	m_y = y;
}

void Peg::setColor(Color color) {
	m_color = color;
}

bool twixt::Peg::operator==(const Peg& peg) const
{
	if (m_x == peg.getX() && m_y == peg.getY() && m_color == peg.getColor())
		return true;
	return false;
}

Position twixt::Peg::getPosition() const
{
	return std::make_pair(m_x, m_y);
}



