#pragma once

#include <iostream>
#include <string>
#include <QPoint>
#include <QColor>
#include "Utils.h"

namespace twixt {

    class Peg {
    public:
        // Constructors and destructor
        Peg();
        Peg(size_t rowOnBoard, size_t columnOnBoard, Color color, QPoint positionOnScreen = QPoint{ 0,0 }, QColor qcolor = QColor{ 0,0,0 });
        Peg(const Peg& peg);
        ~Peg();

        // Getter functions
        size_t getRowOnBoard() const;
        size_t getColumnOnBoard() const;
        Color getColor() const;
        Position getPosition() const;
        QPoint getPositionOnScreen() const;
        QColor getQColor() const;

        // Setter functions
        void setRowOnBoard(uint16_t rowOnBoard);
        void setColumnOnBoard(uint16_t columnOnBoard);
        void setColor(Color color);
        void setPositionOnScreen(QPoint positionOnScreen);
        void setQColor(QColor qcolor);

        // Comparison operator
        bool operator==(const Peg& peg) const;

    private:
        // Member variables
        size_t m_rowOnBoard;
        size_t m_columnOnBoard;
        QPoint m_positionOnScreen;
        Color m_color;
        QColor m_qcolor;
    };
}
