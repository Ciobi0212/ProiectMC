#include "Twixt.h"

Peg::Peg() = default;

Peg::Peg(size_t rowOnBoard, size_t columnOnBoard, Color color) : m_rowOnBoard{ rowOnBoard }, m_columnOnBoard{ columnOnBoard }, m_color{ color } {}

Peg::~Peg() = default;

size_t Peg::getRowOnBoard() const {
    return m_rowOnBoard;
}

size_t Peg::getColumnOnBoard() const {
    return m_columnOnBoard;
}

Color Peg::getColor() const {
    return m_color;
}

void Peg::setRowOnBoard(uint16_t rowOnBoard) {
    m_rowOnBoard = rowOnBoard;
}

void Peg::setColumnOnBoard(uint16_t columnOnBoard) {
    m_columnOnBoard = columnOnBoard;
}

void Peg::setColor(Color color) {
    m_color = color;
}

bool Peg::operator==(const Peg& peg) const {
    return m_rowOnBoard == peg.m_rowOnBoard && m_columnOnBoard == peg.m_columnOnBoard;
}

Position Peg::getPosition() const {
    return Position{ m_rowOnBoard, m_columnOnBoard };
}


Link::Link(Peg& p1, Peg& p2, Color color) : m_p1{ p1 }, m_p2{ p2 }, m_color{ color } {}

Link::~Link() = default;

Peg& Link::getP1() const {
	return m_p1;
}

Peg& Link::getP2() const {
	return m_p2;
}

Color Link::getColor() const {
	return m_color;
}

void Link::setColor(Color color)
{
	m_color = color;
}

void Link::setP1(Peg& p1) {
	m_p1 = p1;
}

void Link::setP2(Peg& p2) {
	m_p2 = p2;
}

Peg& Link::getOtherEnd(const Peg& peg) const
{
	if (peg == m_p1)
		return m_p2;
	else if (peg == m_p2)
		return m_p1;
}

Cell::Cell() {
	m_peg = nullptr;
	m_links = std::unordered_set<Link*>();
	m_color = Color::NONE;
}



Cell::~Cell() = default;

Color Cell::getColor() const {
	return m_color;
}

Peg& Cell::getPeg() const {
	if (m_peg)
		return *m_peg;
	else
		throw std::exception("Cell has no peg");
}

std::unordered_set<Link*> Cell::getLinks() const
{
	return m_links;
}

void Cell::setColor(Color color) {
	m_color = color;
}

void Cell::setPeg(Peg* peg) {
	m_peg = peg;
}

void Cell::addLink(Link* link)
{
	m_links.insert(link);
}

void Cell::removeLink(Link* link)
{
	m_links.erase(link);
}

bool Cell::hasPeg() const {
	if (m_peg == nullptr) {
		return false;
	}

	return true;
}

bool Cell::hasLinks() const
{
	if (m_links.size() == 0) {
		return false;
	}

	return true;
}


Board::Board(size_t BOARD_SIZE) : BOARD_SIZE{ BOARD_SIZE } {
	m_board.resize(BOARD_SIZE);
	for (std::size_t i = 0; i < BOARD_SIZE; i++)
		m_board[i].resize(BOARD_SIZE);
};


Board::~Board() = default;

size_t Board::getSize() const
{
	return BOARD_SIZE;
}

bool Board::isInBounds(const Position& pos) const
{
	auto& [line, column] = pos;

	return line >= 0 && line < BOARD_SIZE && column >= 0 && column < BOARD_SIZE;
}

Cell& Board::operator[](const Position& pos)
{
	auto& [line, column] = pos;

	if (!isInBounds(pos))
		throw std::out_of_range("Position out of bounds");

	return m_board[line][column];

}

const Cell& Board::operator[](const Position& pos) const
{
	auto& [line, column] = pos;

	if (!isInBounds(pos))
		throw std::out_of_range("Position out of bounds");

	return m_board[line][column];
}



Player::Player() = default;

Player::Player(const std::string& name, Color color, BaseType baseType, uint8_t numPegs, uint8_t numLinks) :
	m_name{ name }, m_color{ color }, m_baseType{ baseType }, m_numPegs{ numPegs }, m_numLinks{ numLinks } {}

Player::~Player() = default;

const std::string& Player::getName() const {
	return m_name;
}

Color Player::getColor() const {
	return m_color;
}

uint8_t Player::getNumPegs() const
{
	return m_numPegs;
}

uint8_t Player::getNumLinks() const
{
	return m_numLinks;
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

void Player::addPeg(Peg& peg)
{
	m_pegs.push_back(peg);
}

void Player::addLink(Link& link)
{
	m_links.push_back(link);
}



bool Player::linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const
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

bool Player::pegCanBePlaced(Board& board, const Position& pos) const
{
	Cell& curentCell = board[pos];

	if (curentCell.hasPeg()) {
		return false;
	}

	//check so that a player doesnt put a peg in the other's player base
	if (m_baseType == BaseType::VERTICAL && (pos.first == 0 || pos.first == board.getSize() - 1)) {
		return false;
	}
	if (m_baseType == BaseType::HORIZONTAL && (pos.second == 0 || pos.second == board.getSize() - 1)) {
		return false;
	}

	return true;
}

bool Player::checkLinkOverlap(Board& board, const Position& pos1, const Position& pos2) const
{
	for (size_t i = 0; i < board.getSize(); i++)
		for (size_t j = 0; j < board.getSize(); j++) {
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



bool Player::checkForWin(Board& board)
{
	std::unordered_set<Position, PositionHash> visited;

	for (size_t i = 0; i < board.getSize(); i++) {
		Position currentPos;

		if (this->getColor() == Color::RED)
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

void Player::placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2)
{
	Link* linkToAdd = new Link{ board[pos1].getPeg(), board[pos2].getPeg(), m_color };
	board[pos1].addLink(linkToAdd);
	board[pos2].addLink(linkToAdd);
	this->addLink(*linkToAdd);
	this->m_numLinks--;
}

void Player::removeLinkFromBoard(Board& board, Link* linkToRemove)
{
	Position pos1 = linkToRemove->getP1().getPosition();
	Position pos2 = linkToRemove->getP2().getPosition();
	board[pos1].removeLink(linkToRemove);
	board[pos2].removeLink(linkToRemove);
	delete linkToRemove;
	this->m_numLinks++;
}

//std::vector<Link*> Player::setLinks(const std::vector<Link*>& links) {
//	this->m_links = links;
//	return this->m_links;
//}

void Player::placePegOnBoard(Board& board, const Position& pos)
{
	Cell& curentCell = board[pos];

	auto& [x, y] = pos;
	Peg* pegToAdd = new Peg{ x, y, m_color };;
	curentCell.setPeg(pegToAdd);
	curentCell.setColor(m_color);
	this->addPeg(*pegToAdd);
	this->m_numPegs--;

	std::vector<Position> validPositions{ { x - 2, y - 1 }, { x - 2, y + 1 }, { x + 2, y - 1 },
										  { x + 2, y + 1 }, { x - 1, y - 2 }, { x - 1, y + 2 },
										  { x + 1, y - 2 }, { x + 1, y + 2 } };
	for (Position& pos : validPositions) {
		if (board.isInBounds(pos)) {
			Cell& cell = board[pos];
			if (cell.hasPeg() && cell.getPeg().getColor() == m_color) {
				Position pos1 = { x, y };
				Position pos2 = pos;
				if (!checkLinkOverlap(board, pos1, pos2)) {
					placeLinkOnBoard(board, pos1, pos2);
				}
			}
		}
	}

}


TwixtGame::TwixtGame() {
	firstPlayer = Player("Player1", Color::RED, BaseType::HORIZONTAL);
	secondPlayer = Player("Player2", Color::BLUE, BaseType::VERTICAL);
	currentPlayer = &firstPlayer;
}

TwixtGame::~TwixtGame() = default;

Board& TwixtGame::getBoard()
{
	return board;
}

void TwixtGame::switchPlayer()
{
	if (currentPlayer->getColor() == firstPlayer.getColor())
	{
		currentPlayer = &secondPlayer;
	}
	else
	{
		currentPlayer = &firstPlayer;
	}
}

Player& TwixtGame::getCurrentPlayer()
{
	return *currentPlayer;
}


