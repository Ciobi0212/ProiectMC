#pragma once
#include "board.h";
#include "player.h";

using namespace twixt;
class TwixtGame
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

