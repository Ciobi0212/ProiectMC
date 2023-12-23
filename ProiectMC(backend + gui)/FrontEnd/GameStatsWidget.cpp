#include "GameStatsWidget.h"

GameStatsWidget::GameStatsWidget(TwixtGame& game, QWidget *parent)
	: QWidget(parent), game{ game }
{
	ui.setupUi(this);
	setFixedSize(800, 100);
}

GameStatsWidget::~GameStatsWidget()
{}

void GameStatsWidget::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	displayGameStats(painter);
}

void GameStatsWidget::displayGameStats(QPainter& painter)
{
	painter.drawText(10, 20, "Current player's turn: ");
	if (game.getCurrentPlayer().getColor() == Color::RED)
		painter.drawText(10, 40, "Red");
	else
		painter.drawText(10, 40, "Blue");
}
