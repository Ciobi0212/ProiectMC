#pragma once
#include "board.h";
#include "player.h";

using namespace twixt;
enum class ActionType {
	PLACE_PEG, PLACE_LINK, NONE
};
using Action = std::tuple<ActionType, Position, Position>;
// Hash function for a tuple of positions using PositionHash
struct PositionsTupleHash {
	template <typename T>
	std::size_t operator()(const T& t) const {
		std::size_t hashValue = 0;
		for (const auto& pos : t) {
			hashValue ^= PositionHash()(pos);
		}
		return hashValue;
	}
};

// Hash function for the Action type using PositionsTupleHash for positions
// Hash function for a pair of integers
// Hash function for the Action type
struct ActionHash {
	std::size_t operator()(const Action& action) const {
		ActionType actionType = std::get<0>(action);
		Position position1 = std::get<1>(action);
		Position position2 = std::get<2>(action);
		return static_cast<std::size_t>(actionType) ^ PositionHash {}(position1) ^ PositionHash {}(position2);
	}
};
using ActionSet = std::unordered_set<Action, ActionHash>;


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
	

	//Helper Functions for AI
	ActionSet getValidActions();
	ActionSet getValidPegActions();
	ActionSet getValidLinkActions();
	ActionSet getValidLinkActionsImproved(Position positionOfLastPegPlaced);
	
	bool isGameOver();
	bool isDraw();
	
	//TwixtGame getNextState(Action& action);
	
	void goToNextState(Action& action);
	//std::pair<double,bool> getValueAndCheckForWin(TwixtGame& state);
	Player& getOpponent(Player& currentPlayer);
	double getOpponnentValue(double value);
	
	
private:
	Board board;
	Player firstPlayer;
	Player secondPlayer;
	Color currentPlayer;
};

