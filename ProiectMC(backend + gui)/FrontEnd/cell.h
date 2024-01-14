#pragma once

#include "Peg.h"
#include "Link.h"

#include <optional>
#include <string>
#include <vector>
#include <unordered_set>
#include <QPoint>

namespace twixt {

    class Cell {
    private:
        Peg* m_peg;
        std::unordered_set<Link*> m_links;
        Color m_color;
        QPoint m_positionOnScreen;

    public:
        // Constructors and destructor
        Cell();
        ~Cell();

        // Getter functions
        Color getColor() const;
        Peg& getPeg() const;
        std::unordered_set<Link*> getLinks() const;
        QPoint getPositionOnScreen() const;

        // Setter functions
        void setColor(Color color);
        void setPositionOnScreen(QPoint position);
        void setPeg(Peg* peg);

        // Link-related functions
        void addLink(Link* link);
        void removeLink(Link* link);

        // Check functions
        bool hasColor() const;
        bool hasPeg() const;
        bool hasLinks() const;
    };
}
