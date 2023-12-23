#pragma once
#include "Peg.h"
using namespace twixt;

class __declspec(dllexport) Link {
public:
	Link(Peg& p1, Peg& p2, Color color);
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
};