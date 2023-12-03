#pragma once


#include <string>;
#include <vector>;
#include "Peg.h";
#include "link.h";
#include "board.h";

namespace twixt {
	 class Player {
	public:
		Player();
		Player(const std::string& name, Color color);
		~Player();
		std::string getName() const;
		Color getColor() const;
		void setName(const std::string& name);
		void setColor(Color color);
		std::vector<std::reference_wrapper<Peg>> getPegs() const;
		std::vector<std::reference_wrapper<Link>> getLinks() const;
		//std::vector<Peg*> setPegs(const std::vector<Peg&>& pegs);
		//std::vector<Link*> setLinks(const std::vector<Link&>& links);
		
		using Position = std::pair<size_t, size_t>;
		
		void placePegOnBoard(Board& board, const Position& pos);
		void placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2);

		void addPeg(Peg& peg);
		void addLink(Link& link);
		bool linkNeedsToBePlaced(Board& board, const Position& pos1, const Position& pos2) const;
	
		
	private:
		std::string m_name;
		Color m_color;
		std::vector<std::reference_wrapper<Peg>> m_pegs;
		std::vector<std::reference_wrapper<Link>> m_links;
	};
}