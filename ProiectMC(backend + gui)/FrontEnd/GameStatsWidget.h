#pragma once

#include <QWidget>
#include "ui_GameStatsWidget.h"
#include "TwixtGame.h"
#include <qpainter.h>
#include "BoardWidget.h"
#include "MCTS.h"

class GameStatsWidget : public QWidget
{
	Q_OBJECT

public:
	GameStatsWidget(TwixtGame& game,BoardWidget& boardWidget, QWidget *parent = nullptr);
	~GameStatsWidget();
	void paintEvent(QPaintEvent* event) override;
	void displayGameStats(QPainter& painter);
private slots:
	void on_pushButtonEndTurn_clicked();
	void on_pushButtonMCTS_clicked();

private:
	Ui::GameStatsWidgetClass ui;
	TwixtGame& game;
	BoardWidget& boardWidget;
};
