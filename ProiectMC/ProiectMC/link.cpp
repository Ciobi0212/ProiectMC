#include "link.h";
using twixt::Link;
using twixt::Peg;

Link::Link(Peg& p1, Peg& p2) : m_p1{ p1 }, m_p2{ p2 } {}

Link::~Link() = default;

Peg Link::getP1() const {
	return m_p1;
}

Peg Link::getP2() const {
	return m_p2;
}

void Link::setP1(Peg& p1) {
	m_p1 = p1;
}

void Link::setP2(Peg& p2) {
	m_p2 = p2;
}

Peg& twixt::Link::getOtherEnd(const Peg& peg) const
{
	if (peg == m_p1)
		return m_p2;
	else if (peg == m_p2)
		return m_p1;
	else
		throw std::exception("Peg not found");
}



