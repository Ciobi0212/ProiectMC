#pragma once

#include <QWidget>
#include "ui_GameStatsWidget.h"
#include "TwixtGame.h"
#include <qpainter.h>
#include "BoardWidget.h"
#include "MCTS.h"
#include <fstream>
#include <qfiledialog.h>

class GameStatsWidget : public QWidget
{
    Q_OBJECT

public:
    GameStatsWidget(TwixtGame& game, BoardWidget& boardWidget, QWidget* parent = nullptr);
    ~GameStatsWidget();

    void paintEvent(QPaintEvent* event) override;
    void displayGameStats(QPainter& painter);

private slots:
    void on_pushButtonEndTurn_clicked();
    void on_pushButtonMCTS_clicked();
    void on_pushButtonSaveGame_clicked();
    void on_pushButtonLoadSave_clicked();

private:
    Ui::GameStatsWidgetClass ui;
    TwixtGame& game;
    BoardWidget& boardWidget;
    std::string savePath;

    // Helper functions
    void drawCurrentPlayer(QPainter& painter);
    void drawPlayerStats(QPainter& painter, const Player& player, int xOffset);
    std::string generateSaveFileName() const;
    void saveBoardState(std::ofstream& saveFile) const;
    void savePegState(std::ofstream& saveFile, const Cell& cell) const;
    void saveLinkState(std::ofstream& saveFile, const Cell& cell, std::unordered_set<Link*>& alreadySaved) const;
};
