#include "cell.h";
using namespace twixt;


Cell::Cell() {
	m_peg = nullptr;
	m_links = std::unordered_set<Link*>();
	m_color = Color::NONE;
}

Cell::~Cell() = default;

Color Cell::getColor() const {
	return m_color;
}

Peg& Cell::getPeg() const {
	if (m_peg)
		return *m_peg;
	else
		throw std::exception("Cell has no peg");
}

std::unordered_set<Link*> Cell::getLinks() const
{
	return m_links;
}

void Cell::setColor(Color color) {
	m_color = color;
}

void Cell::setPeg(Peg* peg) {
	m_peg = peg;
}

void Cell::addLink(Link* link)
{
	m_links.insert(link);
}

void Cell::removeLink(Link* link)
{
	m_links.erase(link);
}

bool Cell::hasPeg() const {
	if (m_peg == nullptr) {
		return false;
	}

	return true;
}

bool Cell::hasLinks() const
{
	if (m_links.size() == 0) {
		return false;
	}

	return true;
}


