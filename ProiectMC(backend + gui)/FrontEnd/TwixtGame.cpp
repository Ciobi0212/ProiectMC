#include "TwixtGame.h"

using namespace twixt;

TwixtGame::TwixtGame() {
	firstPlayer = Player("Player1", Color::RED, BaseType::HORIZONTAL,50,50, Qt::red);
	secondPlayer = Player("Player2", Color::BLUE, BaseType::VERTICAL,50,50, Qt::blue);
	currentPlayer = firstPlayer.getColor();
}

TwixtGame::~TwixtGame() = default;

TwixtGame::TwixtGame(TwixtGame& other) : board{ other.board }, firstPlayer{ other.firstPlayer }, secondPlayer{ other.secondPlayer }, currentPlayer{ other.currentPlayer } {}

Board& TwixtGame::getBoard() { return board; }

void TwixtGame::switchPlayer() {
	Player& current = getCurrentPlayer();
	current.setPlacedPeg(false);
	current.setSelectedPeg(nullptr);
	currentPlayer = (currentPlayer == firstPlayer.getColor()) ? secondPlayer.getColor() : firstPlayer.getColor();
}

Player& TwixtGame::getCurrentPlayer() { return (currentPlayer == firstPlayer.getColor()) ? firstPlayer : secondPlayer; }

Player& TwixtGame::getFirstPlayer() { return firstPlayer; }

Player& TwixtGame::getSecondPlayer() { return secondPlayer; }

void TwixtGame::setCurrentPlayer(Color color) { currentPlayer = color; }

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
	if (currentPlayer.getNumOfPegsLeft() == 0)
		return validActions;
	

	for (int i = 0; i < board.getSize(); i++)
	{
		for (int j = 0; j < board.getSize(); j++)
		{
			Position pos1 = Position(i, j);
			if (currentPlayer.pegCanBePlaced(board, pos1))
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

ActionSet TwixtGame::getValidLinkActionsImproved(Position positionOfLastPegPlaced)
{
	Player& currentPlayer = getCurrentPlayer();
	ActionSet validActions;
	auto [i, j] = positionOfLastPegPlaced;
	std::vector<Position> validPositions{ { i - 2, j - 1 }, { i - 2, j + 1 }, { i + 2, j - 1 },
				{ i + 2, j + 1 }, { i - 1, j - 2 }, { i - 1, j + 2 },
				{ i + 1, j - 2 }, { i + 1, j + 2 } };

	
		for (Position posOfPeg : validPositions)
		{
			if (currentPlayer.linkCanBePlaced(board, posOfPeg, positionOfLastPegPlaced))
			{
				if (posOfPeg > positionOfLastPegPlaced)
					validActions.insert(std::make_tuple(ActionType::PLACE_LINK, positionOfLastPegPlaced, posOfPeg));
				else
				validActions.insert(std::make_tuple(ActionType::PLACE_LINK, posOfPeg, positionOfLastPegPlaced));
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

void TwixtGame::goToNextState(Action& action)
{
	ActionType actionType = std::get<0>(action);
	Board& board = getBoard();
	if (actionType == ActionType::PLACE_PEG)
	{
		Position pos1 = std::get<1>(action);
		getCurrentPlayer().placePegOnBoard(board, pos1);
	}
	else if (actionType == ActionType::PLACE_LINK)
	{
		Position pos1 = std::get<1>(action);
		Position pos2 = std::get<2>(action);
		getCurrentPlayer().placeLinkOnBoard(board, pos1, pos2);
	}
}




