#pragma once
#include <unordered_set>
#include "Link.h"
using namespace twixt;

class __declspec(dllexport) Cell {
private:
	Peg* m_peg;
	std::unordered_set<Link*> m_links;
	Color m_color;

public:
	Cell();
	~Cell();
	Color getColor() const;
	Peg& getPeg() const;
	std::unordered_set<Link*> getLinks() const;
	void setColor(Color color);
	void setPeg(Peg* peg);
	void addLink(Link* link);
	void removeLink(Link* link);
	bool hasPeg() const;
	bool hasLinks() const;

};
