#pragma once

#include <iostream>
#include "Peg.h"

namespace twixt {

    class Link {
    public:
        // Constructors and destructor
        Link(Peg& p1, Peg& p2, Color color, QColor qcolor = QColor{ 0,0,0 });
        ~Link();

        // Getter functions
        Peg& getP1() const;
        Peg& getP2() const;
        Color getColor() const;

        // Setter functions
        void setColor(Color color);
        void setP1(Peg& p1);
        void setP2(Peg& p2);

        // Other functions
        Peg& getOtherEnd(const Peg& peg) const;

    private:
        Peg& m_p1;
        Peg& m_p2;
        Color m_color;
        QColor m_qcolor;
    };
}
