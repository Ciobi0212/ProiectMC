#pragma once


#include <string>;
#include <vector>;
#include "qtPeg.h";
#include "qtLink.h";
#include "board.h";

namespace twixt {
	enum class BaseType {
		VERTICAL, HORIZONTAL
	};

	class QtPlayer {
	public:
		QtPlayer();
		QtPlayer(const std::string& name, Color color, BaseType baseType,
			QColor qcolor = Qt::white, uint8_t numPegs = 50, uint8_t numLinks = 50);
		
		~QtPlayer();
		const std::string& getName() const;
		Color getColor() const;
		QColor getQColor() const;
		uint8_t getNumPegs() const;
		uint8_t getNumLinks() const;
		void setName(const std::string& name);
		void setColor(Color color);
		void setQColor(QColor qcolor);
		

		void placePegOnBoard(Board& board, const Position& pos);
		void placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2);
		void removeLinkFromBoard(Board& board, qtLink* linkToRemove);
		void addPeg(qtPeg& peg);
		void addLink(qtLink& link);

		bool linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const;
		bool pegCanBePlaced(Board& board, const Position& pos) const;
		bool checkLinkOverlap(Board& board, const Position& pos1, const Position& pos2) const;
		bool checkForWin(Board& board);




	private:
		std::string m_name;
		Color m_color;
		QColor m_qcolor;
		BaseType m_baseType;
		uint8_t m_numPegs;
		uint8_t m_numLinks;
	};
}