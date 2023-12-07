#pragma once


#include "peg.h";

#include "link.h";

#include <optional>;
#include <string>;
#include <vector>

namespace twixt {
	 class Cell {
	private:
		Peg* m_peg;
		std::vector<Link*> m_links;
		Color m_color;

	public:
		Cell();
		~Cell();
		Color getColor() const;
	    Peg& getPeg() const;
		std::vector<Link*> getLinks() const;
		void setColor(Color color);
		void setPeg(Peg* peg);
		void addLink(Link* link);
		bool hasColor() const;
		bool hasPeg() const;
		bool hasLinks() const;

	};
}