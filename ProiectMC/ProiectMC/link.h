#pragma once
#include <iostream>
#include "peg.h";

namespace twixt {
	export class Link {
	public:
		Link();
		Link(const Peg& p1, const Peg& p2);
		~Link();
		Peg getP1() const;
		Peg getP2() const;
		std::string getColor() const;
		Peg setP1(const Peg& p1);
		Peg setP2(const Peg& p2);
		std::string setColor(const std::string& color);
		//Player owner; (implement Player class)

	private:
		Peg m_p1;
		Peg m_p2;
		std::string color;

	};
}