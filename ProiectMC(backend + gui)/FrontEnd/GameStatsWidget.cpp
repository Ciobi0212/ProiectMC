#include "GameStatsWidget.h"

GameStatsWidget::GameStatsWidget(TwixtGame& game, BoardWidget& boardWidget, QWidget* parent)
	: QWidget(parent), game{ game }, boardWidget{ boardWidget }
{
	ui.setupUi(this);
	setFixedSize(800, 100);
}

GameStatsWidget::~GameStatsWidget()
{}

void GameStatsWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	displayGameStats(painter);
}

void GameStatsWidget::displayGameStats(QPainter& painter)
{
	painter.drawText(10, 20, "Current player's turn: ");
	if (game.getCurrentPlayer().getColor() == Color::RED)
	{
		//coloraza textul rosu
		painter.setPen(QColor(255, 0, 0));
		painter.drawText(10, 40, "Red");
	}
	else
	{
		//coloraza textul albastru
		painter.setPen(QColor(0, 0, 255));
		painter.drawText(10, 40, "Blue");
	}
}

void GameStatsWidget::on_pushButtonEndTurn_clicked()
{
	game.switchPlayer();
	boardWidget.repaint();
	repaint();
}

void GameStatsWidget::on_pushButtonMCTS_clicked() {
	MCTS mcts(game);
	mcts.best_action(10000);
}