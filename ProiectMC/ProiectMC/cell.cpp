#include "cell.h";
using twixt::Cell;
using twixt::Link;
using twixt::Peg;


Cell::Cell() = default;

Cell::~Cell() = default;

std::optional<std::string> Cell::getColor() const {
	return m_color;
}

Peg& Cell::getPeg() const {
	if (m_peg.has_value())
		return *m_peg.value();
	else
		throw std::exception("Cell has no peg");
}

Link& Cell::getLink() const {
	if (m_link.has_value())
		return *m_link.value();
	else
		throw std::exception("Cell has no link");
}

void Cell::setColor(const std::string& color) {
	m_color.emplace(color);
}

void Cell::setPeg(Peg*& peg) {
	m_peg.emplace(peg);
}

void Cell::setLink(Link*& link) {
	m_link.emplace(link);
}

bool Cell::hasColor() const {
	return m_color.has_value();
}

bool Cell::hasPeg() const {
	return m_peg.has_value();
}


