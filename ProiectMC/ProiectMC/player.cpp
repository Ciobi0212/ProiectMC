#include "player.h"
using twixt::Player;
using twixt::Peg;
using twixt::Link;


Player::Player() = default;

Player::Player(std::string name, std::string color) : name{ name }, color{ color } {}

Player::~Player() = default;

std::string Player::getName() const {
	return name;
}

std::string Player::getColor() const {
	return color;
}

std::string Player::setName(const std::string& name) {
	this->name = name;
	return this->name;
}

std::string Player::setColor(const std::string& color) {
	this->color = color;
	return this->color;
}

std::vector<Peg> Player::getPegs() const {
	return pegs;
}

std::vector<Link> Player::getLinks() const {
	return links;
}

std::vector<Peg> Player::setPegs(std::vector<Peg> pegs) {
	this->pegs = pegs;
	return this->pegs;
}

std::vector<Link> Player::setLinks(std::vector<Link> links) {
	this->links = links;
	return this->links;
}

