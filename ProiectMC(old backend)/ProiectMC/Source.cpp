#include <iostream>
#include "TwixtGame.h"

using namespace twixt;


int main() {
	
	Player* player1 = new Player("Player1", Color::RED, BaseType::HORIZONTAL);
		Player * player2 = new Player("Player2", Color::BLUE, BaseType::VERTICAL);
	Board* board = new Board();


	player1->placePegOnBoard(*board, { 0, 1 });
	//place the pegs in a manner so that player1 wins
	player1->placePegOnBoard(*board, {2,2});
	player2->placePegOnBoard(*board, { 0,2 });
	player2->placePegOnBoard(*board, { 2,1 });

	//place links beetween the pegs
	
	
}