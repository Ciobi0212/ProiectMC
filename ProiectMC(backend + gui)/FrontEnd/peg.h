#pragma once
#include <iostream>;
#include <string>;
#include <qpoint.h>
#include <qcolor.h>
#include "Utils.h"


namespace twixt {

	class Peg {
	public:
		Peg();
		Peg(size_t rowOnBoard, size_t columnOnBoard, Color color, QPoint positionOnScreen = QPoint{ 0,0 }, QColor qcolor = QColor{ 0,0,0 });
		Peg(const Peg& peg);
		~Peg();
		size_t getRowOnBoard() const;
		size_t getColumnOnBoard() const;
		Color getColor() const;
		void setRowOnBoard(uint16_t rowOnBoard);
		void setColumnOnBoard(uint16_t columnOnBoard);
		void setColor(Color color);
		bool operator==(const Peg& peg) const;
		Position getPosition() const;
		QPoint getPositionOnScreen() const;
		QColor getQColor() const;
		void setPositionOnScreen(QPoint positionOnScreen);
		void setQColor(QColor qcolor);


	private:
		size_t m_rowOnBoard;
		size_t m_columnOnBoard;
		QPoint m_positionOnScreen;
		Color m_color;
		QColor m_qcolor;
	};
}