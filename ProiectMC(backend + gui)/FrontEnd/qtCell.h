#pragma once
#include "qtLink.h";
#include <string>;
#include <vector>
#include <unordered_set>
#include <qpoint.h>

namespace twixt {
	 class qtCell {
	private:
		qtPeg* m_peg;
		std::unordered_set<qtLink*> m_links;
		Color m_color;
		QPoint m_positionOnScreen;

	public:
		qtCell();
		~qtCell();
		Color getColor() const;
	    qtPeg& getPeg() const;
		std::unordered_set<qtLink*> getLinks() const;
		void setColor(Color color);
		void setPositionOnScreen(QPoint position);
		QPoint getPositionOnScreen() const;
		void setPeg(qtPeg* peg);
		void addLink(qtLink* link);
		void removeLink(qtLink* link);
		bool hasColor() const;
		bool hasPeg() const;
		bool hasLinks() const;

	};
}