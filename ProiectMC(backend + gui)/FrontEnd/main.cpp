#include "FrontEnd.h"
#include "PMT.h"
#include <QtWidgets/QApplication>
#include "MCTS.h"
#include <fstream>

int main(int argc, char* argv[])
{
	/*QApplication a(argc, argv);
	TwixtGame game;
	FrontEnd w(game);
	w.show();
	return a.exec();*/

	//test MCTS
	TwixtGame game;
	Board& board = game.getBoard();
	Player& player = game.getCurrentPlayer();
	/*player.placePegOnBoard(board, Position(0, 3));
	player.placePegOnBoard(board, Position(2, 2));
	player.placePegOnBoard(board, Position(4, 3));
	player.placePegOnBoard(board, Position(6, 2));
	player.placePegOnBoard(board, Position(8, 3));
	player.placePegOnBoard(board, Position(10, 2));
	player.placePegOnBoard(board, Position(12, 3));
	player.placePegOnBoard(board, Position(14, 2));
	player.placePegOnBoard(board, Position(16, 3));
	player.placePegOnBoard(board, Position(18, 2));
	player.placePegOnBoard(board, Position(20, 3));
	player.placePegOnBoard(board, Position(22, 2));
	player.placeLinkOnBoard(board, Position(0, 3), Position(2, 2));
	player.placeLinkOnBoard(board, Position(2, 2), Position(4, 3));
	player.placeLinkOnBoard(board, Position(4, 3), Position(6, 2));
	player.placeLinkOnBoard(board, Position(6, 2), Position(8, 3));
	player.placeLinkOnBoard(board, Position(8, 3), Position(10, 2));
	player.placeLinkOnBoard(board, Position(10, 2), Position(12, 3));
	player.placeLinkOnBoard(board, Position(12, 3), Position(14, 2));
	player.placeLinkOnBoard(board, Position(14, 2), Position(16, 3));
	player.placeLinkOnBoard(board, Position(16, 3), Position(18, 2));
	player.placeLinkOnBoard(board, Position(18, 2), Position(20, 3));
	player.placeLinkOnBoard(board, Position(20, 3), Position(22, 2));
	player.placePegOnBoard(board, Position(23, 2));*/
	
	
	
	
	/*
	game.getCurrentPlayer().placePegOnBoard(board, Position(3, 0));
	game.getCurrentPlayer().placePegOnBoard(board, Position(1, 1));
	game.getCurrentPlayer().placePegOnBoard(board, Position(4, 2));
	game.switchPlayer();
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(0, 3), Position(2, 2));
	game.switchPlayer();
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(3, 0), Position(4, 2));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(7, 5));
	game.getCurrentPlayer().placePegOnBoard(board, Position(1, 6));
	game.getCurrentPlayer().placePegOnBoard(board, Position(0, 5));
	game.getCurrentPlayer().placePegOnBoard(board, Position(5, 6));
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(5, 6), Position(7, 5));
	game.getCurrentPlayer().placePegOnBoard(board, Position(7, 3));
	game.getCurrentPlayer().placePegOnBoard(board, Position(4, 3));
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(2, 2), Position(4, 3));
	game.getCurrentPlayer().placePegOnBoard(board, Position(6, 4));*/



	//RALUCA VS CIOBOT (CIOBOT WINS EASILY)
	/*game.getCurrentPlayer().placePegOnBoard(board, Position(5, 3));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(1, 1));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(0, 5));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(3, 2));
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(1, 1), Position(3, 2));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(4, 5));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(1, 3));
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(3, 2), Position(1, 3));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(7, 4));
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(5, 3), Position(7, 4));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(2, 5));
	game.getCurrentPlayer().placeLinkOnBoard(board, Position(1, 3), Position(2, 5));
	game.switchPlayer();*/
	

	//game.getCurrentPlayer().placePegOnBoard(board, Position(0, 3));
	//game.getCurrentPlayer().placePegOnBoard(board, Position(2, 2));
	//game.getCurrentPlayer().placePegOnBoard(board, Position(4, 3));
	//game.getCurrentPlayer().placePegOnBoard(board, Position(5, 5));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(0, 3), Position(2, 2));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(2, 2), Position(4, 3));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(4, 3), Position(5, 5));
	//game.switchPlayer();
	//game.getCurrentPlayer().placePegOnBoard(board, Position(3, 5));
	//game.getCurrentPlayer().placePegOnBoard(board, Position(6, 4));
	//game.getCurrentPlayer().placePegOnBoard(board, Position(5, 2));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(5, 2), Position(6, 4));
	//game.getCurrentPlayer().placePegOnBoard(board, Position(5, 6));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(3, 5), Position(5, 6));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(6, 4), Position(5, 6));
	//game.getCurrentPlayer().placePegOnBoard(board, Position(5, 2));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(6, 4), Position(5, 2));
	//
	

 //   MCTS mcts(game);
	//Action action = mcts.best_action(1000);

  

	//game.getCurrentPlayer().placePegOnBoard(board, Position(11, 4));
	//game.switchPlayer();
	////put 5 3 
	//game.getCurrentPlayer().placePegOnBoard(board, Position(5, 3));
	//game.switchPlayer();
	////put 0 2
	//game.getCurrentPlayer().placePegOnBoard(board, Position(0, 2));
	//game.switchPlayer();
	//
	//game.getCurrentPlayer().placePegOnBoard(board, Position(6, 1));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(6, 1), Position(5, 3));
	//game.switchPlayer();
	////put 9 7 
	//game.getCurrentPlayer().placePegOnBoard(board, Position(9, 7));
	//game.switchPlayer();
	////put 7 4 
	//game.getCurrentPlayer().placePegOnBoard(board, Position(7, 4));
	////put link 7 4 5 3
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(7, 4), Position(5, 3));
	//game.switchPlayer();
	////6 10
	//game.getCurrentPlayer().placePegOnBoard(board, Position(6, 10));
	//game.switchPlayer();
	//// 6 6
	//game.getCurrentPlayer().placePegOnBoard(board, Position(6, 6));
	////ling 6 6 7 4
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(6, 6), Position(7, 4));
	//game.switchPlayer();
	////3 8
	//game.getCurrentPlayer().placePegOnBoard(board, Position(3, 8));
	//game.switchPlayer();
	////4 7
	//game.getCurrentPlayer().placePegOnBoard(board, Position(4, 7));
	////link 6 6 4 7
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(6, 6), Position(4, 7));
	//game.switchPlayer();
	//
	//game.getCurrentPlayer().placePegOnBoard(board, Position(5, 7));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(5, 7), Position(3, 8));
	//game.switchPlayer();
	////7 8
	//game.getCurrentPlayer().placePegOnBoard(board, Position(7, 8));
	////7 8  6 6
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(7, 8), Position(6, 6));
	//game.switchPlayer();
	////8 9 
	//game.getCurrentPlayer().placePegOnBoard(board, Position(8, 9));
	////8 9 9 7
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(8, 9), Position(9, 7));
	////8 9 6 10
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(8, 9), Position(6, 10));
	//game.switchPlayer();
	////5 9
	//game.getCurrentPlayer().placePegOnBoard(board, Position(5, 9));
	////5 9 7 8
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(5, 9), Position(7, 8));
	//game.switchPlayer();
	//// 4 9
	//game.getCurrentPlayer().placePegOnBoard(board, Position(4, 9));
	////4 9 6 10
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(4, 9), Position(6, 10));
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(5, 7), Position(4, 9));
	//game.switchPlayer();
	////2 8 
	//game.getCurrentPlayer().placePegOnBoard(board, Position(2, 8));
	////2 8 4 7
	//game.getCurrentPlayer().placeLinkOnBoard(board, Position(2, 8), Position(4, 7));
	//game.switchPlayer();
   //BEST OUTPUT: 1 9
	

//put 8 8
game.getCurrentPlayer().placePegOnBoard(board, Position(8, 8));
game.switchPlayer();
//5 0
game.getCurrentPlayer().placePegOnBoard(board, Position(5, 0));
game.switchPlayer();
//9 6
game.getCurrentPlayer().placePegOnBoard(board, Position(9, 6));
//9 6 8 8
game.getCurrentPlayer().placeLinkOnBoard(board, Position(9, 6), Position(8, 8));
game.switchPlayer();
//5 4
game.getCurrentPlayer().placePegOnBoard(board, Position(5, 4));
game.switchPlayer();
//3 8
game.getCurrentPlayer().placePegOnBoard(board, Position(3, 8));
game.switchPlayer();
// 4 2
game.getCurrentPlayer().placePegOnBoard(board, Position(4, 2));
//4 2 5 4
game.getCurrentPlayer().placeLinkOnBoard(board, Position(4, 2), Position(5, 4));
//4 2 5 0
game.getCurrentPlayer().placeLinkOnBoard(board, Position(4, 2), Position(5, 0));
game.switchPlayer();
//9 5 
game.getCurrentPlayer().placePegOnBoard(board, Position(9, 5));
game.switchPlayer();
//4 6
game.getCurrentPlayer().placePegOnBoard(board, Position(4, 6));
//4 6 5 4 
game.getCurrentPlayer().placeLinkOnBoard(board, Position(4, 6), Position(5, 4));
game.switchPlayer();


	MCTS mcts(game);
	//PMT pm;
    //pm.getBestAction(game, 2000);
	Action action = mcts.best_action(5000);
	

	//(0,3), (2,2), (5,3)
	//(3,0), (1,1), (4,2)
	
	
	
	return 0;
	
}
