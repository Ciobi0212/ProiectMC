#pragma once
export module player;

#include <string>;
#include <vector>;
#include "peg.h";
#include "link.h";

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
		std::vector<Peg> getPegs() const;
		std::vector<Link> getLinks() const;
		std::vector<Peg> setPegs(std::vector<Peg> pegs);
		std::vector<Link> setLinks(std::vector<Link> links);
	private:
		std::string name;
		std::string color;
		std::vector<Peg> pegs;
		std::vector<Link> links;
	};
}