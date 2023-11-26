#pragma once


#include "peg.h";

#include "link.h";

#include <optional>;
#include <string>;

namespace twixt {
	 class Cell {
	private:
		std::optional<std::string> m_color;
		std::optional<Peg*> m_peg;
		std::optional<Link*> m_link;

	public:
		Cell();
		//		TwixtCell(const std::string& color, const Peg& peg, const Link& link);
		~Cell();
		std::optional<std::string> getColor() const;
		Peg& getPeg() const;
		Link& getLink() const;
		void setColor(const std::string& color);
		void setPeg(Peg*& peg);
		void setLink(Link*& link);
		bool hasColor() const;
		bool hasPeg() const;

	};
}