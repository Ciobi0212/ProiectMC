#pragma once
#include "Board.h"
#include "Player.h"
using namespace twixt;
class __declspec(dllexport) TwixtGame
{
public:
	TwixtGame();
	~TwixtGame();
	Board& getBoard();
	void switchPlayer();
	Player& getCurrentPlayer();

private:
	Board board;
	Player firstPlayer;
	Player secondPlayer;
	Player* currentPlayer;

};
