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
		Player(std::string name, std::string color);
		~Player();
		std::string getName() const;
		std::string getColor() const;
		std::string setName(const std::string& name);
		std::string setColor(const std::string& color);
		std::vector<std::reference_wrapper<Peg>> getPegs() const;
		std::vector<std::reference_wrapper<Link>> getLinks() const;
		//std::vector<Peg*> setPegs(const std::vector<Peg&>& pegs);
		void addPeg(Peg& peg);
		void addLink(Link& link);
		//std::vector<Link*> setLinks(const std::vector<Link&>& links);
		
		using Position = std::pair<uint8_t, uint8_t>;
		
		void placePegOnBoard(Board& board, const Position& pos);
	private:
		std::string m_name;
		std::string m_color;
		std::vector<std::reference_wrapper<Peg>> m_pegs;
		std::vector<std::reference_wrapper<Link>> m_links;
	};
}