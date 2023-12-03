
#include <iostream>
#include "TwixtGame.h"

using namespace twixt;


int main() {
	
	Player* player1 = new Player("Player1", Color::RED);
	Player* player2 = new Player("Player2", Color::BLUE);
	Board* board = new Board();

	TwixtGame game(*board, *player1, *player2, *player1);

	player1->placePegOnBoard(*board, { 1, 1 });
	player1->placePegOnBoard(*board, { 1, 2 });
	player1->placePegOnBoard(*board, { 3, 2 });
	player2->placePegOnBoard(*board, { 1, 3 });
	
	auto links = player1->getLinks();
	
	board->drawBoard();
	
	
}