#include "player.h"
#include "queue"
using namespace twixt;

Player::Player() = default;

Player::Player(const std::string& name, Color color, BaseType baseType,
	uint8_t numOfPegsLeft, uint8_t numOfLinksLeft, QColor qcolor, bool placedPeg, Peg* selectedPeg) :
	m_name{ name }, m_color{ color }, m_baseType{ baseType }, m_qcolor{ qcolor },
	m_numOfPegsLeft{ numOfPegsLeft }, m_numOfLinksLeft{ numOfLinksLeft }, m_placedPeg{ placedPeg }, m_selectedPeg{ selectedPeg } {}

Player::Player(const Player& other) {
	*this = other;
}

Player::~Player() = default;

const std::string& Player::getName() const {
	return m_name;
}

uint8_t Player::getNumOfPegsLeft() const {
	return m_numOfPegsLeft;
}

uint8_t Player::getNumOfLinksLeft() const {
	return m_numOfLinksLeft;
}

Color Player::getColor() const {
	return m_color;
}

QColor Player::getQColor() const {
	return m_qcolor;
}

Peg* Player::getSelectedPeg() const {
	return m_selectedPeg;
}

bool Player::getPlacedPeg() const {
	return m_placedPeg;
}

void Player::setName(const std::string& name) {
	m_name = name;
}

void Player::setColor(Color color) {
	m_color = color;
}

void Player::setQColor(QColor qcolor) {
	m_qcolor = qcolor;
}

void Player::setNumOfPegsLeft(uint8_t numOfPegsLeft) {
	m_numOfPegsLeft = numOfPegsLeft;
}

void Player::setNumOfLinksLeft(uint8_t numOfLinksLeft) {
	m_numOfLinksLeft = numOfLinksLeft;
}

void Player::setPlacedPeg(bool status) {
	m_placedPeg = status;
}

void Player::setSelectedPeg(Peg* selectedPeg) {
	m_selectedPeg = selectedPeg;
}

void Player::resetPlayer() {
	m_numOfPegsLeft = 50;
	m_numOfLinksLeft = 50;
	m_placedPeg = false;
	m_selectedPeg = nullptr;
}

bool twixt::Player::linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const
{
	size_t x = pos2.first;
	size_t y = pos2.second;

	if (!(board.isInBounds(pos1) && board.isInBounds(pos2))) {
		return false;
	}
	
	if (!board[pos1].hasPeg() || !board[pos2].hasPeg()) {
		return false;
	}
	
	if (board[pos1].getPeg().getColor() != m_color || board[pos2].getPeg().getColor() != m_color) {
		return false;
	}
	
	for (auto link : board[pos1].getLinks()) {
		if (link->getOtherEnd(board[pos1].getPeg()).getPosition() == pos2) {
			return false;
		}
	}

	std::vector<Position> validPositions{ { x - 2, y - 1 }, { x - 2, y + 1 }, { x + 2, y - 1 },
										  { x + 2, y + 1 }, { x - 1, y - 2 }, { x - 1, y + 2 },
										  { x + 1, y - 2 }, { x + 1, y + 2 } };

	
	if (!std::any_of(validPositions.begin(), validPositions.end(), [&](const Position& pos) { return pos == pos1; })) {
		return false;
	}

	if (checkLinkOverlapImproved(board, pos1, pos2)) {
		return false;
	}
	
	return true;
}

bool twixt::Player::imaginaryLinkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const
{
	if (!(board.isInBounds(pos1) && board.isInBounds(pos2))) {
		return false;
	}
	
	if (!((board[pos1].hasPeg() && board[pos1].getPeg().getColor() == m_color) || (board[pos2].hasPeg() && board[pos2].getPeg().getColor() == m_color))) {
		return false;
	}

	if (board[pos1].getPeg().getColor() != m_color && board[pos2].getPeg().getColor() != m_color) {
		return false;
	}
	
	if (checkLinkOverlapImproved(board, pos1, pos2)) {
		return false;
	}

	return true;
}

bool twixt::Player::pegCanBePlaced(Board& board, const Position& pos) const
{
	Cell& curentCell = board[pos];
	//check pos is not corner cell
	if (pos.first == 0 && pos.second == 0) {
		return false;
	}
	if (pos.first == 0 && pos.second == board.getSize() - 1) {
		return false;
	}
	if (pos.first == board.getSize() - 1 && pos.second == 0) {
		return false;
	}
	if (pos.first == board.getSize() - 1 && pos.second == board.getSize() - 1) {
		return false;
	}

	if (curentCell.hasPeg()) {
		return false;
	}

	if (m_baseType == BaseType::VERTICAL && (pos.first == 0 || pos.first == board.getSize() - 1)) {
		return false;
	}
	if (m_baseType == BaseType::HORIZONTAL && (pos.second == 0 || pos.second == board.getSize() - 1)) {
		return false;
	}
	
	return true;
}

bool twixt::Player::checkLinkOverlapImproved(Board& board, const Position& posOne, const Position& posTwo) const
{
	Position pos1 = posOne ,pos2 = posTwo ,pos3, pos4, pos5, pos6;
	if (pos1.second > pos2.second)
	{
		Position aux = pos1;
		pos1 = pos2;
		pos2 = aux;
	}

	//vertical to the left
	if (pos2.second - pos1.second == 1 && pos2.first - pos1.first == 2)
	{
		pos3 = { pos1.first , pos1.second + 1 };
		pos4 = { pos1.first + 1, pos1.second };
		pos5 = { pos1.first + 1, pos1.second + 1 };
		pos6 = { pos1.first + 2, pos1.second };
	}

	//vertical to the right 
	else if (pos2.second - pos1.second == 1 && pos1.first - pos2.first == 2)
	{
		pos3 = { pos1.first , pos1.second + 1 };
		pos4 = { pos1.first - 1, pos1.second };
		pos5 = { pos1.first - 1, pos1.second + 1 };
		pos6 = { pos1.first - 2, pos1.second };
	}

	//horizontal to the top
	else if (pos1.first - pos2.first == 1 && pos2.second - pos1.second == 2)
	{
		pos3 = { pos1.first , pos1.second + 1 };
		pos4 = { pos1.first, pos1.second + 2 };
		pos5 = { pos1.first - 1, pos1.second };
		pos6 = { pos1.first - 1, pos1.second + 1 };
	}

	//horozintal the the bottom
	else if (pos2.first - pos1.first == 1 && pos2.second - pos1.second == 2)
	{
		pos3 = { pos1.first , pos1.second + 1 };
		pos4 = { pos1.first, pos1.second + 2 };
		pos5 = { pos1.first + 1, pos1.second };
		pos6 = { pos1.first + 1, pos1.second + 1 };
	}

	auto checkOverlapForPosition = [&](const Position& pos) {
		if (board.isInBounds(pos) && board[pos].hasLinks()) {
			for (Link* link : board[pos].getLinks()) {
				auto [x1, y1] = posOne;
				auto [x2, y2] = posTwo;
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
						return (val > 0) ? 1 : 2; // clock or counterclockwise 
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
		return false;
		};

	return checkOverlapForPosition(pos3) || checkOverlapForPosition(pos4) || checkOverlapForPosition(pos5) || checkOverlapForPosition(pos6);
}



bool twixt::Player::checkForWin(Board& board) const
{
	std::unordered_set<Position, PositionHash> visited;

	for (size_t i = 0; i < board.getSize(); i++) {
		Position currentPos;
		if(getColor() == Color::RED)
			currentPos = { 0,i };
		else
		    currentPos = { i,0 };
		
		if (board[currentPos].hasLinks())
		{
			std::queue<Peg> bfsQueue;
			bfsQueue.push(board[currentPos].getPeg());
			visited.insert(currentPos);
			while (!bfsQueue.empty()) {
				Peg currentPeg = bfsQueue.front();
				Position currentPos = currentPeg.getPosition();
				bfsQueue.pop();
				auto& [line, column] = currentPos;

				if ((line == board.getSize() - 1 && m_color == Color::RED) || (column == board.getSize() - 1 && m_color == Color::BLUE))
					return true;

				std::unordered_set<Link*> links = board[currentPos].getLinks();
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

void twixt::Player::initValidPegPositions( Board& board)
{
	m_validPegPositions.clear();
	
	for (size_t i = 0; i < board.getSize(); i++) {
		for (size_t j = 0; j < board.getSize(); j++) {
			if (pegCanBePlaced(board, { i,j }))
				m_validPegPositions.insert({ ActionType::PLACE_PEG,{ i, j },{i,j} });
		}
	}
}

ActionSet& twixt::Player::getValidPegPositions()
{
	return m_validPegPositions;
}

void twixt::Player::eraseValidPegPosition(const Action& action)
{
	m_validPegPositions.erase(action);
}

Player& twixt::Player::operator=(const Player& other)
{
	if (this != &other) {
		m_name = other.m_name;
		m_color = other.m_color;
		m_baseType = other.m_baseType;
		m_qcolor = other.m_qcolor;
		m_numOfPegsLeft = other.m_numOfPegsLeft;
		m_numOfLinksLeft = other.m_numOfLinksLeft;
		m_validPegPositions = other.m_validPegPositions;
	}
	return *this;
}

void twixt::Player::placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2)
{
	Link* linkToAdd = new Link{ board[pos1].getPeg(), board[pos2].getPeg(), m_color };
	board[pos1].addLink(linkToAdd);
	board[pos2].addLink(linkToAdd);
	this->m_numOfLinksLeft--;
}

void twixt::Player::removeLinkFromBoard(Board& board, Link* linkToRemove)
{
	Position pos1 = linkToRemove->getP1().getPosition();
	Position pos2 = linkToRemove->getP2().getPosition();
	board[pos1].removeLink(linkToRemove);
	board[pos2].removeLink(linkToRemove);
	delete linkToRemove;
	this->m_numOfLinksLeft++;
}

void twixt::Player::placePegOnBoard(Board& board, const Position& pos)
{
	if (m_placedPeg) // Player already placed a peg in this turn
		return;
	
	Cell& curentCell = board[pos];
	
	auto& [x, y] = pos;
	Peg* pegToAdd = new Peg{ x, y, m_color, curentCell.getPositionOnScreen(), m_qcolor};
	curentCell.setPeg(pegToAdd);
	curentCell.setColor(m_color);
	this->m_numOfPegsLeft--;
	m_validPegPositions.erase({ ActionType::PLACE_PEG, pos,pos });
	m_placedPeg = true;

}








