#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FrontEnd.h"
#include "TwixtGame.h"
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <qmessagebox.h>

using namespace twixt;

constexpr uint16_t widthRes = 800;
constexpr uint16_t heightRes = 800;
constexpr uint8_t radius = 5;

class FrontEnd : public QMainWindow
{
    Q_OBJECT

public:
    FrontEnd(QWidget* parent = nullptr);
    ~FrontEnd();
    void drawBoard(QPainter& painter);

    void drawPegsAndLinks(QPainter& painter);
    void drawCellContent(QPainter& painter, Cell& cell);
    void drawEmptyCell(QPainter& painter, Cell& cell);
    void drawPeg(QPainter& painter, Peg& peg);
    void setPegColor(QPainter& painter, Color color);
    void setLinkColor(QPainter& painter, Color color);
    void drawLinksOfCell(QPainter& painter, const Cell& cell);
    bool isCornerCell(size_t row, size_t col, size_t boardSize);
	bool isClickOnCell(QPoint click, Cell& cell);
	bool isClickOnLink(QPoint click, Link* link);
	void handleCellClick(const Position& pos, Player& currentPlayer, Board& board);
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Ui::FrontEndClass ui;
    TwixtGame game;
    size_t boardSize;
    size_t radius;
    size_t cellSize;
    QPoint startPoint;
	QPoint endPoint;
	bool isDrawingLink;
};
