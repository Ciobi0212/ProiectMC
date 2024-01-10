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
		Player(const std::string& name, Color color, BaseType baseType, 
			uint8_t numOfPegsLeft = 50, uint8_t numOfLinksLeft = 50, QColor qcolor = Qt::white, 
			bool placedPeg = false, Peg* selectedPeg = nullptr);

		Player(const Player& other);
		~Player();
		const std::string& getName() const;
		uint8_t getNumOfPegsLeft() const;
		uint8_t getNumOfLinksLeft() const;
		Color getColor() const;
		QColor getQColor() const;
		Peg* getSelectedPeg() const;
		void setName(const std::string& name);
		void setColor(Color color);
		void setQColor(QColor qcolor);
		void setNumOfPegsLeft(uint8_t numOfPegsLeft);
		void setNumOfLinksLeft(uint8_t numOfLinksLeft);
		void setPlacedPeg(bool status);
		void setSelectedPeg(Peg* selectedPeg);
		//std::vector<std::reference_wrapper<Peg>> getPegs() const;
		//std::vector<std::reference_wrapper<Link>> getLinks() const;
		//std::vector<Peg*> setPegs(const std::vector<Peg&>& pegs);
		//std::vector<Link*> setLinks(const std::vector<Link&>& links);
		
		void placePegOnBoard(Board& board, const Position& pos);
		void placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2);
		void removeLinkFromBoard(Board& board, Link* linkToRemove);
		
		
		bool linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const;
		bool pegCanBePlaced(Board& board, const Position& pos) const;
		bool checkLinkOverlap(Board& board, const Position& pos1, const Position& pos2) const;
		bool checkLinkOverlapImproved(Board& board, const Position& pos1, const Position& pos2) const;
		bool checkForWin(Board& board);
		bool checkOverlapHelper(const Position& pos1, const Position& pos2, Link* link) const;

		// = operator
		Player& operator=(const Player& other);
		
		
	
		
	private:
		std::string m_name;
		Color m_color;
		uint8_t m_numOfPegsLeft;
		uint8_t m_numOfLinksLeft;
		QColor m_qcolor;
		BaseType m_baseType;
		bool m_placedPeg{false};
		Peg* m_selectedPeg{nullptr};
		//std::vector<std::reference_wrapper<Peg>> m_pegs;
		//std::vector<std::reference_wrapper<Link>> m_links;
	};
}