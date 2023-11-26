#include "player.h"
using twixt::Player;
using twixt::Peg;
using twixt::Link;


Player::Player() = default;

Player::Player(std::string name, std::string color) : m_name{ name }, m_color{ color } {}

Player::~Player() = default;

std::string Player::getName() const {
	return m_name;
}

std::string Player::getColor() const {
	return m_color;
}

std::string Player::setName(const std::string& name) {
	this->m_name = name;
	return this->m_name;
}

std::string Player::setColor(const std::string& color) {
	this->m_color = color;
	return this->m_color;
}

std::vector<std::reference_wrapper<Peg>> Player::getPegs() const {
	return m_pegs;
}

std::vector<std::reference_wrapper<Link>> Player::getLinks() const {
	return m_links;
}

//std::vector<Peg*> Player::setPegs(const std::vector<Peg*>& pegs) {
//	this->m_pegs = pegs;
//	return this->m_pegs;
//}

void twixt::Player::addPeg(Peg& peg)
{
	m_pegs.push_back(peg);
}

void twixt::Player::addLink(Link& link)
{
	m_links.push_back(link);
}

//std::vector<Link*> Player::setLinks(const std::vector<Link*>& links) {
//	this->m_links = links;
//	return this->m_links;
//}

void twixt::Player::placePegOnBoard(Board& board, const Position& pos) 
{
	Cell& curentCell = board[pos];
	
	if (curentCell.hasPeg()) {
		throw std::runtime_error("Cell already has a peg");
	}
	
	auto& [x, y] = pos;
	Peg* pegToAdd = new Peg{ x, y, m_color };

	curentCell.setPeg(pegToAdd);
	this->addPeg(*pegToAdd);
	
	Position upLeft{ x - 2, y - 1 };
	Position upRight{ x - 2, y + 1 };
	Position downLeft{ x + 2, y - 1 };
	Position downRight{ x + 2, y + 1 };
	uint16_t boardSize = board.getSize();
	
	if (board.isInBounds(upLeft)) {
		if (board[upLeft].hasPeg() and board[upLeft].getPeg().getColor() == m_color) {
			Link* link = new Link(*pegToAdd, board[upLeft].getPeg());
			addLink(*link);
			curentCell.setLink(link);
		}
	}
	
	if (board.isInBounds(upRight)) {
		if (board[upRight].hasPeg() and board[upRight].getPeg().getColor() == m_color) {
			Link* link = new Link(*pegToAdd, board[upRight].getPeg());
			addLink(*link);
			curentCell.setLink(link);
		}
	}
	
	if (board.isInBounds(downLeft)) {
		if (board[downLeft].hasPeg() and board[downLeft].getPeg().getColor() == m_color) {
			Link* link = new Link(*pegToAdd, board[downLeft].getPeg());
			addLink(*link);
			curentCell.setLink(link);
		}
	}
	
	if (board.isInBounds(downRight)) {
		if (board[downRight].hasPeg() and board[downRight].getPeg().getColor() == m_color) {
			Link* link = new Link(*pegToAdd, board[downRight].getPeg());
			addLink(*link);
			curentCell.setLink(link);
		}
	}
	
}

