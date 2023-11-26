#include "link.h";
using twixt::Link;
using twixt::Peg;

Link::Link(Peg& p1, Peg& p2) : m_p1{ p1 }, m_p2{ p2 } {
	m_color = m_p1.getColor();
}

Link::~Link() = default;

Peg Link::getP1() const {
	return m_p1;
}

Peg Link::getP2() const {
	return m_p2;
}

std::string Link::getColor() const {
	return m_color;
}

void Link::setP1(Peg& p1) {
	m_p1 = p1;
}

void Link::setP2(Peg& p2) {
	m_p2 = p2;
}

void Link::setColor(const std::string& color) {
	m_color = color;
}

