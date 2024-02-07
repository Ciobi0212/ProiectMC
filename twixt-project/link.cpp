#include "link.h"

namespace twixt {

    Link::Link(Peg& p1, Peg& p2, Color color, QColor qcolor)
        : m_p1{ p1 }, m_p2{ p2 }, m_color{ color }, m_qcolor{ qcolor } {}

    Link::~Link() = default;

    Peg& Link::getP1() const {
        return m_p1;
    }

    Peg& Link::getP2() const {
        return m_p2;
    }

    Color Link::getColor() const {
        return m_color;
    }

    void Link::setColor(Color color) {
        m_color = color;
    }

    void Link::setP1(Peg& p1) {
        m_p1 = p1;
    }

    void Link::setP2(Peg& p2) {
        m_p2 = p2;
    }

    Peg& Link::getOtherEnd(const Peg& peg) const {
        if (peg == m_p1)
            return m_p2;
        else if (peg == m_p2)
            return m_p1;
        else
            throw std::exception("Peg not found");
    }

} 
