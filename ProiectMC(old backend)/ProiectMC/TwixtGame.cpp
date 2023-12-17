#include "TwixtGame.h"

using namespace twixt;

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



