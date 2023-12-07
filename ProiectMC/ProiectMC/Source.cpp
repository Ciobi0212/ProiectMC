#include <iostream>
#include "TwixtGame.h"

using namespace twixt;


int main() {
	
	Player* player1 = new Player("Player1", Color::RED);
	Player* player2 = new Player("Player2", Color::BLUE);
	Board* board = new Board();

	TwixtGame game(*board, *player1, *player2, *player1);

	player1->placePegOnBoard(*board, { 0, 1 });
	//place the pegs in a manner so that player1 wins
	player1->placePegOnBoard(*board, {2,2});
	player1->placePegOnBoard(*board, { 4,1 });
	
	board->drawBoard();
	std::cout<<player1->checkWin(*board);
	
	
}