#include "player.h"
using namespace twixt;
#include <unordered_set>
#include <queue>

Player::Player() = default;

Player::Player(const std::string& name, Color color, BaseType baseType, Peg* selectedPeg) : m_name{ name }, m_color{ color }, m_baseType{ baseType }, m_selectedPeg{selectedPeg} {}

Player::~Player() = default;

const std::string& Player::getName() const {
	return m_name;
}

Color Player::getColor() const {
	return m_color;
}

Peg* twixt::Player::getSelectedPeg() const
{
	return m_selectedPeg;
}

void Player::setName(const std::string& name) {
	this->m_name = name;
}

void Player::setColor(Color color) {
	this->m_color = color;
}

void twixt::Player::setSelectedPeg(Peg* selectedPeg)
{
	m_selectedPeg = selectedPeg;
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



bool twixt::Player::linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const
{
	size_t x = pos2.first;
	size_t y = pos2.second;
	
	std::vector<Position> validPositions{ { x - 2, y - 1 }, { x - 2, y + 1 }, { x + 2, y - 1 }, { x + 2, y + 1 }, { x - 1, y - 2 }, { x - 1, y + 2 }, { x + 1, y - 2 }, { x + 1, y + 2 } };

	for (Position& position : validPositions) {
		if (pos1 == position)
			return true;
		}
	
	return false;
}

bool twixt::Player::pegCanBePlaced(Board& board, const Position& pos) const
{
	Cell& curentCell = board[pos];

	if (curentCell.hasPeg()) {
		return false;
	}

	//check so that a player doesnt put a peg in the other's player base
	if (m_baseType == BaseType::VERTICAL && (pos.first == 0 || pos.first == Board::BOARD_SIZE - 1)) {
		return false;
	}
	if (m_baseType == BaseType::HORIZONTAL && (pos.second == 0 || pos.second == Board::BOARD_SIZE - 1)) {
		return false;
	}
	
	return true;
}

bool twixt::Player::checkLinkOverlap(Board& board, const Position& pos1, const Position& pos2) const
{
	for (size_t i = 0; i < Board::BOARD_SIZE; i++)
		for (size_t j = 0; j < Board::BOARD_SIZE; j++) {
			if (board[{i, j}].hasLinks()) {
				std::unordered_set<Link*> links = board[{i, j}].getLinks();
				for (Link* link : links) {
					auto [x1, y1] = pos1;
					auto [x2, y2] = pos2;
					auto [x3, y3] = link->getP1().getPosition();
					auto [x4, y4] = link->getP2().getPosition();
					
					if ((x1 == x3 && y1 == y3 && link->getP1().getColor() == m_color) ||
						(x1 == x4 && y1 == y4 && link->getP2().getColor() == m_color) ||
						(x2 == x3 && y2 == y3 && link->getP1().getColor() == m_color) ||
						(x2 == x4 && y2 == y4 && link->getP2().getColor() == m_color))
						continue;
					
					else {
						auto orientation = [](const Position& p1, const Position& p2, const Position& p3) {
							int val = (p2.second - p1.second) * (p3.first - p2.first) -
								(p2.first - p1.first) * (p3.second - p2.second);
							if (val == 0) return 0;  // colinear 
							return (val > 0) ? 1 : 2; // clock or counterclock wise 
							};

						int o1 = orientation({ x1, y1 }, { x2, y2 }, { x3, y3 });
						int o2 = orientation({ x1, y1 }, { x2, y2 }, { x4, y4 });
						int o3 = orientation({ x3, y3 }, { x4, y4 }, { x1, y1 });
						int o4 = orientation({ x3, y3 }, { x4, y4 }, { x2, y2 });
						if (o1 != o2 && o3 != o4)
							return true;
					}
				}
			}
		}
	return false;
}



bool twixt::Player::checkForWin(Board& board)
{
	std::unordered_set<Position, PositionHash> visited;

	for (size_t i = 0; i < Board::BOARD_SIZE; i++) {
		if (board[{0, i}].hasLinks())
		{
			Position currentPos = { 0,i };
			std::queue<Peg> bfsQueue;
			bfsQueue.push(board[currentPos].getPeg());
			visited.insert(currentPos);
			while (!bfsQueue.empty()) {
				Peg currentPeg = bfsQueue.front();
				Position currentPos = currentPeg.getPosition();
				bfsQueue.pop();
				auto& [line, column] = currentPos;

				if ((line == Board::BOARD_SIZE - 1 && m_color == Color::RED) || (column == Board::BOARD_SIZE - 1 && m_color == Color::BLUE))
					return true;

				std::unordered_set<Link*> links = std::move(board[currentPos].getLinks());
				for (Link* link : links) {
					Peg& nextPeg = link->getOtherEnd(board[currentPos].getPeg());
					Position nextPos = nextPeg.getPosition();
					if (visited.find(nextPos) == visited.end()) {
						bfsQueue.push(nextPeg);
						visited.insert(nextPos);
					}
				}
			}
		}
	}
	return false;
}

void twixt::Player::placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2)
{
	Link* linkToAdd = new Link{ board[pos1].getPeg(), board[pos2].getPeg(), m_color };
	board[pos1].addLink(linkToAdd);
	board[pos2].addLink(linkToAdd);
	this->addLink(*linkToAdd);
}

//std::vector<Link*> Player::setLinks(const std::vector<Link*>& links) {
//	this->m_links = links;
//	return this->m_links;
//}

void twixt::Player::placePegOnBoard(Board& board, const Position& pos)
{
	Cell& curentCell = board[pos];
	
	auto& [x, y] = pos;
	Peg* pegToAdd = new Peg{ x, y, m_color };
	curentCell.setPeg(pegToAdd);
	curentCell.setColor(m_color);
	this->addPeg(*pegToAdd);

	std::vector<Position> validPositions{ { x - 2, y - 1 }, { x - 2, y + 1 }, { x + 2, y - 1 }, { x + 2, y + 1 }, { x - 1, y - 2 }, { x - 1, y + 2 }, { x + 1, y - 2 }, { x + 1, y + 2 } };
	for (Position& pos : validPositions) {
		if (board.isInBounds(pos)) {
			Cell& cell = board[pos];
			if (cell.hasPeg() && cell.getPeg().getColor() == m_color){
				Position pos1 = { x, y };
				Position pos2 = pos;
				if (!checkLinkOverlap(board, pos1, pos2)) {
					placeLinkOnBoard(board, pos1, pos2);
				}
			}
		}
	}

}








