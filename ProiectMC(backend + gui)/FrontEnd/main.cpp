#include "FrontEnd.h"
#include "PMT.h"
#include <QtWidgets/QApplication>
#include "MCTS.h"
#include <fstream>

int main(int argc, char* argv[])
{
	std::string savePath = "SavedGames";
	QApplication a(argc, argv);
	TwixtGame game;
	FrontEnd w(game);
	w.show();
	return a.exec();
}
