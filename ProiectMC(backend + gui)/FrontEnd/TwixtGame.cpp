#include "TwixtGame.h"

using namespace twixt;

TwixtGame::TwixtGame() {
	firstPlayer = Player("Player1", Color::RED, BaseType::HORIZONTAL, Qt::red);
	secondPlayer = Player("Player2", Color::BLUE, BaseType::VERTICAL, Qt::blue);
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



