#pragma once
export module cell;

#include "peg.h";

#include "link.h";

#include <optional>;
#include <string>;

namespace twixt {
	export class Cell {
	private:
		std::optional<std::string> m_color;
		std::optional<Peg*> m_peg;
		std::optional<Link*> m_link;

	public:
		Cell();
		//		TwixtCell(const std::string& color, const Peg& peg, const Link& link);
		~Cell();
		std::optional<std::string> getColor() const;
		std::optional<Peg*> getPeg() const;
		std::optional<Link*> getLink() const;
		void setColor(const std::string& color);
		void setPeg(const Peg& peg);
		void setLink(const Link& link);
		bool hasColor() const;
		bool hasPeg() const;

	};
}