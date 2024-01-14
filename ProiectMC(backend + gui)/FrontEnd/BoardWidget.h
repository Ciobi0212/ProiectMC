#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <QMessageBox>
#include <fstream>
#include <thread>

#include "ui_BoardWidget.h"
#include "TwixtGame.h"

using namespace twixt;

constexpr uint16_t boardWidth = 700;
constexpr uint16_t boardHeight = 700;
constexpr uint16_t radius = 5;

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    // Constructors and destructor
    BoardWidget(TwixtGame& game, QWidget* parent = nullptr);
    ~BoardWidget();

    // Event handlers
    void mousePressEvent(QMouseEvent* event) override;

public:
    // Drawing functions
    void paintEvent(QPaintEvent* event) override;
    void drawBoard(QPainter& painter);
    void drawBaseDelimitators(QPainter& painter);
    void drawCellContent(QPainter& painter, const Cell& cell);
    void drawEmptyCell(QPainter& painter, const Cell& cell);
    void drawPeg(QPainter& painter, Peg& peg);
    void drawLinksOfCell(QPainter& painter, const Cell& cell);
    void drawRecommandations(QPainter& painter);

    // Helper functions
    bool isCornerCell(size_t row, size_t col, size_t boardSize) const;
    bool isClickOnCell(QPoint click, Cell& cell) const;
    bool isClickOnLink(QPoint click, Link* link) const;
    void setScreenCoordsForCells();

    // Event handling functions
    void handleCellClick(const Position& pos, Player& currentPlayer, Board& board);
    void handleLinkClick(Link* link, Player& currentPlayer, Board& board);

    // Message functions
    void winMessage(const Player& player);

    // Other functions
    void setRecommendedActions(const std::vector<Action>& actions);
    void clearRecommendedActions();
    void loadSave(const std::string& saveGamePath);
    void resetGame();

private:
    Ui::BoardWidgetClass ui;
    TwixtGame& game;
    size_t boardSize;
    size_t cellSize;
    std::vector<Action> recommendedActions;
};
