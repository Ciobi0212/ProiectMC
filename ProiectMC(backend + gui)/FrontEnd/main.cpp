#include "FrontEnd.h"
#include "PMT.h"
#include <QtWidgets/QApplication>
#include "MCTS.h"
#include <fstream>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	TwixtGame game;
	FrontEnd w(game);
	w.show();
	return a.exec();

	//test MCTS
	/*TwixtGame game;
	Board& board = game.getBoard();
	Player& player = game.getCurrentPlayer();*/
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
	player.placeLinkOnBoard(board, Position(20, 3), Position(22, 2));*/
	//player.placePegOnBoard(board, Position(23, 4));
	
	

	/*player.placePegOnBoard(board, Position(0, 1));
	player.placePegOnBoard(board, Position(2, 2));
	player.placePegOnBoard(board, Position(4, 3));
	player.placeLinkOnBoard(board, Position(0, 1), Position(2, 2));
	player.placeLinkOnBoard(board, Position(2, 2), Position(4, 3));
	game.switchPlayer();
	game.getCurrentPlayer().placePegOnBoard(board, Position(4, 1));
	game.getCurrentPlayer().placePegOnBoard(board, Position(4, 5));
	game.getCurrentPlayer().placePegOnBoard(board, Position(5, 3));
	game.getCurrentPlayer().placePegOnBoard(board, Position(6, 0));*/
	
	
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
	PMT pmt;

	Action action = pmt.getBestAction(game, 1000);
	
	

	//(0,3), (2,2), (5,3)
	//(3,0), (1,1), (4,2)
	
	
	
	
	
}
