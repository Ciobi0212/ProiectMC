#include "link.h";
using twixt::Link;
using twixt::Peg;

Link::Link() = default;

Link::Link(const Peg& p1, const Peg& p2) : m_p1{ p1 }, m_p2{ p2 } {}

Link::~Link() = default;

Peg Link::getP1() const {
	return m_p1;
}

Peg Link::getP2() const {
	return m_p2;
}

std::string Link::getColor() const {
	return color;
}

Peg Link::setP1(const Peg& p1) {
	m_p1 = p1;
	return m_p1;
}

Peg Link::setP2(const Peg& p2) {
	m_p2 = p2;
	return m_p2;
}

std::string Link::setColor(const std::string& color) {
	this->color = color;
	return this->color;
}

