#pragma once
#include "board.h";
#include "player.h";


class TwixtGame
{
public:
	TwixtGame(twixt::Board& board, twixt::Player& firstPlayer, twixt::Player& secondPlayer, twixt::Player& currentPlayer);
	~TwixtGame();
	void start();
	void end();
	void reset();

private:
	twixt::Board& board;
	twixt::Player& firstPlayer;
	twixt::Player& secondPlayer;
	twixt::Player& currentPlayer;

};

