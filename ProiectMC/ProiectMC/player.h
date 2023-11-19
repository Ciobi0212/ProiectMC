#pragma once
export module player;

#include <string>;
#include <vector>;
#include "Peg.h";
#include "link.h";
#include "board.h";

namespace twixt {
	export class Player {
	public:
		Player();
		Player(std::string name, std::string color);
		~Player();
		std::string getName() const;
		std::string getColor() const;
		std::string setName(const std::string& name);
		std::string setColor(const std::string& color);
		std::vector<Peg*> getPegs() const;
		std::vector<Link*> getLinks() const;
		std::vector<Peg*> setPegs(const std::vector<Peg*>& pegs);
		std::vector<Link*> setLinks(const std::vector<Link*>& links);
		
		using Position = std::pair<uint8_t, uint8_t>;
		
		void placePegOnBoard(Board& board, const Position& pos) const;
	private:
		std::string m_name;
		std::string m_color;
		std::vector<Peg*> m_pegs;
		std::vector<Link*> m_links;
	};
}