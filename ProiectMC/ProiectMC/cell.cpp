#include "cell.h";
using twixt::Cell;
using twixt::Link;
using twixt::Peg;

import <optional>;
import <string>;

Cell::Cell() = default;

Cell::~Cell() = default;

std::optional<std::string> Cell::getColor() const {
	return m_color;
}

std::optional<Peg*> Cell::getPeg() const {
	return m_peg;
}

std::optional<Link*> Cell::getLink() const {
	return m_link;
}

void Cell::setColor(const std::string& color) {
	m_color.emplace(color);
}

void Cell::setPeg(const Peg& peg) {
	m_peg.emplace(peg);
}

void Cell::setLink(const Link& link) {
	m_link.emplace(link);
}

bool Cell::hasColor() const {
	return m_color.has_value();
}

bool Cell::hasPeg() const {
	return m_peg.has_value();
}


