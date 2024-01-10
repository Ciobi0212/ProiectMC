#include "GameStatsWidget.h"

GameStatsWidget::GameStatsWidget(TwixtGame& game, BoardWidget& boardWidget, QWidget* parent)
	: QWidget(parent), game{ game }, boardWidget{ boardWidget }
{
	ui.setupUi(this);
	setFixedSize(800, 100);
}

GameStatsWidget::~GameStatsWidget() = default;


void GameStatsWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	displayGameStats(painter);
}

void GameStatsWidget::displayGameStats(QPainter& painter)
{
	//set bigger font
	QFont font = painter.font();
	font.setPointSize(12);
	painter.setFont(font);
	
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

	painter.setPen(QColor(255, 0, 0));
	painter.drawText(200, 20, "Number of pegs: ");
	painter.drawText(330, 20, QString::number(game.getFirstPlayer().getNumOfPegsLeft()));
	painter.drawText(200, 40, "Number of links: ");
	painter.drawText(330, 40, QString::number(game.getFirstPlayer().getNumOfLinksLeft()));
	
	
	painter.setPen(QColor(0, 0, 255));
	painter.drawText(400, 20, "Number of pegs: ");
	painter.drawText(530, 20, QString::number(game.getSecondPlayer().getNumOfPegsLeft()));
	painter.drawText(400, 40, "Number of links: ");
	painter.drawText(530, 40, QString::number(game.getSecondPlayer().getNumOfLinksLeft()));
	
}

void GameStatsWidget::on_pushButtonEndTurn_clicked()
{
	game.switchPlayer();
	boardWidget.repaint();
	repaint();
}

void GameStatsWidget::on_pushButtonMCTS_clicked() {
	MCTS mcts(game);
	boardWidget.setRecommendedAction(mcts.best_action(10000));
	boardWidget.repaint();
	
}