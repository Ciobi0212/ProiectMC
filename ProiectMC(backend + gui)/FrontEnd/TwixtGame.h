#pragma once
#include "board.h";
#include "player.h";
#include <fstream>
#include <regex>

using namespace twixt;

class TwixtGame
{
public:
	TwixtGame();
	~TwixtGame();
	TwixtGame(TwixtGame& other);
	Board& getBoard();
	void switchPlayer();
	Player& getCurrentPlayer();
	Player& getFirstPlayer();
	Player& getSecondPlayer();
	void setCurrentPlayer(Color color);
	

	//Helper Functions for AI
	ActionSet getValidActions();
	ActionSet getValidPegActions();
	ActionSet getValidLinkActions();
	ActionSet getValidLinkActionsImproved(Position positionOfLastPegPlaced);
	
	bool isGameOver();
	bool isDraw();
	
	void goToNextState(Action& action);
	
	
	
private:
	Board board;
	Player firstPlayer;
	Player secondPlayer;
	Color currentPlayer;
};

