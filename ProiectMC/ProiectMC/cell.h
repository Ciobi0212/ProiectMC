#pragma once


#include "peg.h";

#include "link.h";

#include <optional>;
#include <string>;

namespace twixt {
	 class Cell {
	private:
		Peg* m_peg;
		Link* m_link;
		Color m_color;

	public:
		Cell();
		~Cell();
		Color getColor() const;
	    Peg& getPeg() const;
	    Link& getLink() const;
		void setColor(Color color);
		void setPeg(Peg*& peg);
		void setLink(Link*& link);
		bool hasColor() const;
		bool hasPeg() const;

	};
}