#include "TwixtGame.h"

using namespace twixt;

TwixtGame::TwixtGame() {
	firstPlayer = Player("Player1", Color::RED, BaseType::HORIZONTAL,50,50, Qt::red);
	secondPlayer = Player("Player2", Color::BLUE, BaseType::VERTICAL,50,50, Qt::blue);
	currentPlayer = firstPlayer.getColor();
}

TwixtGame::~TwixtGame() {
}

TwixtGame::TwixtGame(TwixtGame& other)
{
	board = other.board;
	firstPlayer = other.firstPlayer;
	secondPlayer = other.secondPlayer;

	
	if (other.currentPlayer == Color::RED)
	{
		currentPlayer = firstPlayer.getColor();
	}
	else
	{
		currentPlayer = secondPlayer.getColor();
	}
}

Board& TwixtGame::getBoard()
{
	return board;
}

void TwixtGame::switchPlayer()
{
	if (currentPlayer == firstPlayer.getColor())
	{
		currentPlayer = secondPlayer.getColor();
	}
	else
	{
		currentPlayer = firstPlayer.getColor();
	}
}


Player& TwixtGame::getCurrentPlayer()
{
	if (currentPlayer == firstPlayer.getColor())
	{
		return firstPlayer;
	}
	else
	{
		return secondPlayer;
	}
}

ActionSet TwixtGame::getValidActions()
{
	ActionSet validActions;
	Player& currentPlayer = getCurrentPlayer();
	for (int i = 0; i < board.getSize(); i++)
	{
		for (int j = 0; j < board.getSize(); j++)
		{
			Position pos1 = Position(i, j);
			if (currentPlayer.pegCanBePlaced(board, pos1) && currentPlayer.getNumOfPegsLeft() > 0)
			{
				validActions.insert(std::make_tuple(ActionType::PLACE_PEG, pos1, pos1));
			}
			else if (board[pos1].hasPeg()) {
				std::vector<Position> validPositions{ { i - 2, j - 1 }, { i - 2, j + 1 }, { i + 2, j - 1 },
					{ i + 2, j + 1 }, { i - 1, j - 2 }, { i - 1, j + 2 },
					{ i + 1, j - 2 }, { i + 1, j + 2 } };
				for (Position pos2 : validPositions)
				{
					if (currentPlayer.linkCanBePlaced(board, pos1, pos2) && currentPlayer.getNumOfLinksLeft() > 0)
					{
						if (pos1 > pos2)
							std::swap(pos1, pos2);
						if (pos1 == Position(6, 2))
							std::cout << "Link can be placed from ";
						
						validActions.insert(std::make_tuple(ActionType::PLACE_LINK, pos1, pos2));
					}
				}
			}
		}
	}
	
	return validActions;
}

ActionSet TwixtGame::getValidPegActions()
{
	ActionSet validActions;
	Player& currentPlayer = getCurrentPlayer();
	for (int i = 0; i < board.getSize(); i++)
	{
		for (int j = 0; j < board.getSize(); j++)
		{
			Position pos1 = Position(i, j);
			if (currentPlayer.pegCanBePlaced(board, pos1) && currentPlayer.getNumOfPegsLeft() > 0)
			{
				validActions.insert(std::make_tuple(ActionType::PLACE_PEG, pos1, pos1));
			}
		}
	}

	return validActions;
}

ActionSet TwixtGame::getValidLinkActions()
{
	ActionSet validActions;
	Player& currentPlayer = getCurrentPlayer();
	for (int i = 0; i < board.getSize(); i++)
	{
		for (int j = 0; j < board.getSize(); j++)
		{
			Position pos1 = Position(i, j);
			if (board[pos1].hasPeg()) {
				std::vector<Position> validPositions{ { i - 2, j - 1 }, { i - 2, j + 1 }, { i + 2, j - 1 },
					{ i + 2, j + 1 }, { i - 1, j - 2 }, { i - 1, j + 2 },
					{ i + 1, j - 2 }, { i + 1, j + 2 } };
				for (Position pos2 : validPositions)
				{
					if (currentPlayer.linkCanBePlaced(board, pos1, pos2))
					{
						if (pos1 > pos2)
							std::swap(pos1, pos2);

						validActions.insert(std::make_tuple(ActionType::PLACE_LINK, pos1, pos2));
					}
				}
			}
		}
	}

	return validActions;
}

bool TwixtGame::isGameOver()
{
	return firstPlayer.checkForWin(board) || secondPlayer.checkForWin(board);
}

bool TwixtGame::isDraw()
{
	return firstPlayer.getNumOfPegsLeft() == 0 && secondPlayer.getNumOfPegsLeft() == 0;
}



TwixtGame TwixtGame::getNextState(Action& action)
{
	TwixtGame nextState = *this;
	Board& board = nextState.getBoard();
	
	ActionType actionType = std::get<0>(action);
	if (actionType == ActionType::PLACE_PEG)
	{
		Position pos1 = std::get<1>(action);
		nextState.getCurrentPlayer().placePegOnBoard(board, pos1);
	}
	else if (actionType == ActionType::PLACE_LINK)
	{
		Position pos1 = std::get<1>(action);
		Position pos2 = std::get<2>(action);
		nextState.getCurrentPlayer().placeLinkOnBoard(board, pos1, pos2);
	}
	return nextState;
}

std::pair<double, bool> TwixtGame::getValueAndCheckForWin(TwixtGame& state)
{
	Player& currentPlayer = state.getCurrentPlayer();
	if (currentPlayer.checkForWin(state.getBoard()))
		return { 1.0, true };

	//if (firstPlayer.getNumOfPegsLeft() == 0 && secondPlayer.getNumOfPegsLeft() == 0)
	//	return { 0.5, true };

	return { 0, false };
}

Player& TwixtGame::getOpponent(Player& currentPlayer)
{
	if (currentPlayer.getColor() == firstPlayer.getColor())
	{
		return secondPlayer;
	}
	else
	{
		return firstPlayer;
	}
}

double TwixtGame::getOpponnentValue(double value)
{
	return value * -1.0;
}



