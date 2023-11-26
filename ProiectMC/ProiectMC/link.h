#pragma once
#include <iostream>
#include "peg.h";

namespace twixt {
	 class Link {
	public:
		Link(Peg& p1, Peg& p2);
		~Link();
		Peg getP1() const;
		Peg getP2() const;
		std::string getColor() const;
		void setP1(Peg& p1);
		void setP2(Peg& p2);
		void setColor(const std::string& color);

	private:
		Peg& m_p1;
		Peg& m_p2;
		std::string m_color;

	};
}