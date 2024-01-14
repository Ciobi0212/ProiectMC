#include "Menu.h"
#include "PMT.h"
#include <QtWidgets/QApplication>
#include "MCTS.h"
#include <fstream>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Menu w;
	w.show();
	return a.exec();
}
