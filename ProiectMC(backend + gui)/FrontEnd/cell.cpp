#include "cell.h"

namespace twixt {

    Cell::Cell()
        : m_peg{ nullptr }, m_color{ Color::NONE }, m_links{}
    {
		//empty constructor
    }

    Cell::~Cell() {
        m_peg = nullptr;
    }

    Color Cell::getColor() const {
        return m_color;
    }

    Peg& Cell::getPeg() const {
        if (m_peg)
            return *m_peg;
        else
            throw std::exception("Cell has no peg");
    }

    std::unordered_set<Link*> Cell::getLinks() const {
        return m_links;
    }

    void Cell::setColor(Color color) {
        m_color = color;
    }

    void Cell::setPositionOnScreen(QPoint position) {
        m_positionOnScreen = position;
    }

    QPoint Cell::getPositionOnScreen() const {
        return m_positionOnScreen;
    }

    void Cell::setPeg(Peg* peg) {
        m_peg = peg;
    }

    void Cell::addLink(Link* link) {
        m_links.insert(link);
    }

    void Cell::removeLink(Link* link) {
        m_links.erase(link);
    }

    bool Cell::hasColor() const {
        return m_color != Color::NONE;
    }

    bool Cell::hasPeg() const {
        return m_peg != nullptr;
    }

    bool Cell::hasLinks() const {
        return !m_links.empty();
    }

}  
