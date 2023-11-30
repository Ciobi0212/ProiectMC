#include "peg.h";
using namespace twixt;

Peg::Peg() = default;

Peg::Peg(uint16_t x, uint16_t y, Color color) : m_x{ x }, m_y{ y }, m_color{color} {}

Peg::~Peg() = default;

uint16_t Peg::getX() const {
	return m_x;
}

uint16_t Peg::getY() const {
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

