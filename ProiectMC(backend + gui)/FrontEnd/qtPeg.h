#pragma once
#include <iostream>;
#include <string>;
#include <qpoint.h>
#include <qcolor.h>


namespace twixt {
	enum class Color { RED, BLUE, NONE };
	using Position = std::pair<size_t, size_t>;
	struct PositionHash {
		std::size_t operator()(const Position& pos) const {
			return std::hash<std::size_t>()(pos.first) ^ std::hash<std::size_t>()(pos.second);
		}
	};
	
	class qtPeg {
	public:
		qtPeg();
		qtPeg(size_t rowOnBoard, size_t columnOnBoard, Color color, QPoint positionOnScreen = QPoint{ 0,0 }, QColor qcolor = QColor{ 0,0,0 });
		~qtPeg();
		size_t getRowOnBoard() const;
		size_t getColumnOnBoard() const;
		Color getColor() const;
		void setRowOnBoard(uint16_t rowOnBoard);
		void setColumnOnBoard(uint16_t columnOnBoard);
		void setColor(Color color);
		bool operator==(const qtPeg& peg) const;
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