#pragma once


#include <string>;
#include <vector>;
#include "Peg.h";
#include "link.h";
#include "board.h";

namespace twixt {
	enum class BaseType {
		VERTICAL, HORIZONTAL
	};
	
	 class Player {
	public:
		Player();
		Player(const std::string& name, Color color, BaseType baseType, QColor qcolor = Qt::white);
		~Player();
		const std::string& getName() const;
		Color getColor() const;
		QColor getQColor() const;
		void setName(const std::string& name);
		void setColor(Color color);
		void setQColor(QColor qcolor);
		std::vector<std::reference_wrapper<Peg>> getPegs() const;
		std::vector<std::reference_wrapper<Link>> getLinks() const;
		//std::vector<Peg*> setPegs(const std::vector<Peg&>& pegs);
		//std::vector<Link*> setLinks(const std::vector<Link&>& links);
		
		void placePegOnBoard(Board& board, const Position& pos);
		void placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2);
		void addPeg(Peg& peg);
		void addLink(Link& link);
		
		bool linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const;
		bool pegCanBePlaced(Board& board, const Position& pos) const;
		bool checkLinkOverlap(Board& board, const Position& pos1, const Position& pos2) const;
		bool checkForWin(Board& board);
		
		
	
		
	private:
		std::string m_name;
		Color m_color;
		QColor m_qcolor;
		BaseType m_baseType;
		std::vector<std::reference_wrapper<Peg>> m_pegs;
		std::vector<std::reference_wrapper<Link>> m_links;
	};
}