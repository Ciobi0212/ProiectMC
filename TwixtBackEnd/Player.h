#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include "Board.h"

namespace twixt {
	enum class BaseType {
		VERTICAL, HORIZONTAL
	};

	class __declspec(dllexport) Player {
	public:
		Player();
		Player(const std::string& name, Color color, BaseType baseType,
			   uint8_t numPegs = 50, uint8_t numLinks = 50);

		~Player();
		const std::string& getName() const;
		Color getColor() const;
		uint8_t getNumPegs() const;
		uint8_t getNumLinks() const;
		void setName(const std::string& name);
		void setColor(Color color);
		std::vector<std::reference_wrapper<Peg>> getPegs() const;
		std::vector<std::reference_wrapper<Link>> getLinks() const;
		//std::vector<Peg*> setPegs(const std::vector<Peg&>& pegs);
		//std::vector<Link*> setLinks(const std::vector<Link&>& links);

		void placePegOnBoard(Board& board, const Position& pos);
		void placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2);
		void removeLinkFromBoard(Board& board, Link* linkToRemove);
		void addPeg(Peg& peg);
		void addLink(Link& link);

		bool linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const;
		bool pegCanBePlaced(Board& board, const Position& pos) const;
		bool checkLinkOverlap(Board& board, const Position& pos1, const Position& pos2) const;
		bool checkForWin(Board& board);




	private:
		std::string m_name;
		Color m_color;
		BaseType m_baseType;
		uint8_t m_numPegs;
		uint8_t m_numLinks;
		std::vector<std::reference_wrapper<Peg>> m_pegs;
		std::vector<std::reference_wrapper<Link>> m_links;
	};
}
