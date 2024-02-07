#include "qtLink.h";
using namespace twixt;

qtLink::qtLink(qtPeg& p1, qtPeg& p2, Color color, QColor qcolor) : m_p1{ p1 }, m_p2{ p2 }, m_color{ color }, m_qcolor{qcolor} {}

qtLink::~qtLink() = default;

qtPeg& qtLink::getP1() const {
	return m_p1;
}

qtPeg& qtLink::getP2() const {
	return m_p2;
}

Color qtLink::getColor() const {
	return m_color;
}

void twixt::qtLink::setColor(Color color)
{
	m_color = color;
}

void qtLink::setP1(qtPeg& p1) {
	m_p1 = p1;
}

void qtLink::setP2(qtPeg& p2) {
	m_p2 = p2;
}

qtPeg& twixt::qtLink::getOtherEnd(const qtPeg& peg) const
{
	if (peg == m_p1)
		return m_p2;
	else if (peg == m_p2)
		return m_p1;
	else
		throw std::exception("Peg not found");
}



