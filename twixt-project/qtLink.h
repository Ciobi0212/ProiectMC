#pragma once
#include <iostream>
#include "qtPeg.h";

namespace twixt {
	class qtLink {
	public:
		qtLink(qtPeg& p1, qtPeg& p2, Color color, QColor qcolor = QColor{ 0,0,0 });
		~qtLink();
		qtPeg& getP1() const;
		qtPeg& getP2() const;
		Color getColor() const;
		void setColor(Color color);
		void setP1(qtPeg& p1);
		void setP2(qtPeg& p2);
		qtPeg& getOtherEnd(const qtPeg& peg) const;

	private:
		qtPeg& m_p1;
		qtPeg& m_p2;
		Color m_color;
		QColor m_qcolor;
	};
}