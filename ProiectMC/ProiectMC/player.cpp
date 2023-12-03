#include "player.h"
using namespace twixt;


Player::Player() = default;

Player::Player(const std::string& name, Color color) : m_name{ name }, m_color{ color } {}

Player::~Player() = default;

std::string Player::getName() const {
	return m_name;
}

Color Player::getColor() const {
	return m_color;
}

void Player::setName(const std::string& name) {
	this->m_name = name;
}

void Player::setColor(Color color) {
	this->m_color = color;
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

bool twixt::Player::linkNeedsToBePlaced(Board& board, const Position& pos1, const Position& pos2) const
{
	return (board.isInBounds(pos1) and board.isInBounds(pos2) 
		and board[pos1].hasPeg() and board[pos2].hasPeg() 
		and (board[pos1].getColor() == board[pos2].getColor()));
}

void twixt::Player::placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2)
{
	Link* linkToAdd = new Link{ board[pos1].getPeg(), board[pos2].getPeg() };
	board[pos1].setLink(linkToAdd);
	board[pos2].setLink(linkToAdd);
	addLink(*linkToAdd);
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
	curentCell.setColor(m_color);
	this->addPeg(*pegToAdd);
	
	Position upLeft{ x - 2, y - 1 };
	Position upRight{ x - 2, y + 1 };
	Position downLeft{ x + 2, y - 1 };
	Position downRight{ x + 2, y + 1 };
	
	if (linkNeedsToBePlaced(board, pos, upLeft)) {
		placeLinkOnBoard(board, pos, upLeft);
	}
	
	if (linkNeedsToBePlaced(board, pos, upRight)) {
		placeLinkOnBoard(board, pos, upRight);
	}

	if (linkNeedsToBePlaced(board, pos, downLeft)) {
		placeLinkOnBoard(board, pos, downLeft);
	}

	if (linkNeedsToBePlaced(board, pos, downRight)) {
		placeLinkOnBoard(board, pos, downRight);
	}
	
}





