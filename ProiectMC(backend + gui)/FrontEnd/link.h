#pragma once
#include <iostream>
#include "peg.h";

namespace twixt {
	 class Link {
	public:
		Link(Peg& p1, Peg& p2, Color color, QColor qcolor = QColor{ 0,0,0 });
		~Link();
		Peg& getP1() const;
		Peg& getP2() const;
		Color getColor() const;
		void setColor(Color color);
		void setP1(Peg& p1);
		void setP2(Peg& p2);
		Peg& getOtherEnd(const Peg& peg) const;

	private:
		Peg& m_p1;
		Peg& m_p2;
		Color m_color;
		QColor m_qcolor;
	};
}