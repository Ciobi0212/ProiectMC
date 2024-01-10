#include "FrontEnd.h"

FrontEnd::FrontEnd(TwixtGame& game, QWidget* parent)
	: QMainWindow(parent), game{ game }
{
	ui.setupUi(this);
	setFixedSize(widthRes, heightRes);
	setWindowTitle("Twixt");

	boardWidget = new BoardWidget(game, this);
	boardWidget->move((widthRes - boardWidget->width()) / 2, (heightRes - boardWidget->height()));

	gameStatsWidget = new GameStatsWidget(game, *boardWidget, this);
	gameStatsWidget->move(0, 0);
}

FrontEnd::~FrontEnd() = default;
