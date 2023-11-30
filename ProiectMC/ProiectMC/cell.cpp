#include "cell.h";
using namespace twixt;


Cell::Cell() = default;

Cell::~Cell() = default;

Color Cell::getColor() const {
	return m_color;
}

const Peg& Cell::getPeg() const {
	if (m_peg)
		return *m_peg;
	else
		throw std::exception("Cell has no peg");
}

const Link& Cell::getLink() const {
	if (m_link)
		return *m_link;
	else
		throw std::exception("Cell has no link");
}

void Cell::setColor(Color color) {
	m_color = color;
}

void Cell::setPeg(Peg*& peg) {
	m_peg = peg;
}

void Cell::setLink(Link*& link) {
	m_link = link;
}

bool Cell::hasColor() const {
	if (m_color == Color::NONE) {
		return false;
	}
	
	return true;
}

bool Cell::hasPeg() const {
	if (m_peg == nullptr) {
		return false;
	}

	return true;
}


