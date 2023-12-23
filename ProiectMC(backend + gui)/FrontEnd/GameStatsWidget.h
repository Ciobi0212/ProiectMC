#pragma once

#include <QWidget>
#include "ui_GameStatsWidget.h"
#include "TwixtGame.h"
#include <qpainter.h>

class GameStatsWidget : public QWidget
{
	Q_OBJECT

public:
	GameStatsWidget(TwixtGame& game, QWidget *parent = nullptr);
	~GameStatsWidget();
	void paintEvent(QPaintEvent* event) override;
	void displayGameStats(QPainter& painter);

private:
	Ui::GameStatsWidgetClass ui;
	TwixtGame& game;
};
