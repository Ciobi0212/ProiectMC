#include "qtCell.h";

using namespace twixt;

qtCell::qtCell() {
    m_peg = nullptr;
    m_links = std::unordered_set<qtLink*>();
    m_color = Color::NONE;
}

qtCell::~qtCell() = default;

Color qtCell::getColor() const {
    return m_color;
}

qtPeg& qtCell::getPeg() const {
    if (m_peg)
        return *m_peg;
    else
        throw std::exception("qtCell has no qtPeg");
}

std::unordered_set<qtLink*> twixt::qtCell::getLinks() const {
    return m_links;
}

void qtCell::setColor(Color color) {
    m_color = color;
}

void twixt::qtCell::setPositionOnScreen(QPoint position) {
    m_positionOnScreen = position;
}

QPoint twixt::qtCell::getPositionOnScreen() const {
    return m_positionOnScreen;
}

void qtCell::setPeg(qtPeg* peg) {
    m_peg = peg;
}

void twixt::qtCell::addLink(qtLink* link) {
    m_links.insert(link);
}

void twixt::qtCell::removeLink(qtLink* link) {
    m_links.erase(link);
}

bool qtCell::hasColor() const {
    return m_color != Color::NONE;
}

bool qtCell::hasPeg() const {
    return m_peg != nullptr;
}

bool twixt::qtCell::hasLinks() const {
    return !m_links.empty();
}
