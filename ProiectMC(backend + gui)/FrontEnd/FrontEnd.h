#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FrontEnd.h"
#include "TwixtGame.h"
#include "BoardWidget.h"
#include "GameStatsWidget.h"

using namespace twixt;

constexpr uint16_t widthRes = 800;
constexpr uint16_t heightRes = 800;


class FrontEnd : public QMainWindow
{
	Q_OBJECT

public:
	FrontEnd(TwixtGame& game, QWidget* parent = nullptr);
	~FrontEnd();

	

private:
	Ui::FrontEndClass ui;
	TwixtGame& game;
	BoardWidget* boardWidget;
	//GameStatsWidget* gameStatsWidget;
};
