#include "TwixtGame.h"

TwixtGame::TwixtGame(twixt::Board& board, twixt::Player& firstPlayer, twixt::Player& secondPlayer, twixt::Player& currentPlayer) : board(board), firstPlayer(firstPlayer), secondPlayer(secondPlayer), currentPlayer(currentPlayer) {
}

TwixtGame::~TwixtGame() = default;



