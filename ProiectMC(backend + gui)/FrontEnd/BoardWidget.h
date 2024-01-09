#pragma once

#include <QWidget>
#include "ui_BoardWidget.h"
#include "TwixtGame.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <qmessagebox.h>
using namespace twixt;

constexpr size_t boardWidth = 650;
constexpr size_t boardHeight = 650;
constexpr uint8_t radius = 5;

class BoardWidget : public QWidget
{
	Q_OBJECT

public:
	BoardWidget(TwixtGame& game, QWidget *parent = nullptr);
	~BoardWidget();
	//Drawing functions
	void drawBoard(QPainter& painter);
	void drawBaseDelimitators(QPainter& painter);
	void drawCellContent(QPainter& painter, const Cell& cell);
	void drawEmptyCell(QPainter& painter, const Cell& cell);
	void drawPeg(QPainter& painter, Peg& peg);
	void drawLinksOfCell(QPainter& painter, const Cell& cell);
	void paintEvent(QPaintEvent* event) override;
	void drawRecommandation(QPainter& painter);

	//Helper functions
	bool isCornerCell(size_t row, size_t col, size_t boardSize);
	bool isClickOnCell(QPoint click, Cell& cell);
	bool isClickOnLink(QPoint click, Link* link);

	//Event handlers
	void handleCellClick(const Position& pos, Player& currentPlayer, Board& board);
	void handleLinkClick(Link* link, Player& currentPlayer, Board& board);
	void mousePressEvent(QMouseEvent* event) override;

	//Message functions
	void winMessage(const Player& player);

	//
	void setRecommendedAction(Action action);

private:
	Ui::BoardWidgetClass ui;
	TwixtGame& game;
	size_t boardSize;
	size_t cellSize;
	Action recommandedAction;
};
