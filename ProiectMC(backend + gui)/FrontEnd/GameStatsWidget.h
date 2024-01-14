#pragma once

#include <QWidget>
#include <QPainter>
#include "ui_GameStatsWidget.h"
#include "TwixtGame.h"
#include <QFileDialog>

#include "BoardWidget.h"
#include "MCTS.h"

class GameStatsWidget : public QWidget
{
    Q_OBJECT

public:
    // Constructors and destructor
    GameStatsWidget(TwixtGame& game, BoardWidget& boardWidget, QWidget* parent = nullptr);
    ~GameStatsWidget();

    // Paint event
    void paintEvent(QPaintEvent* event) override;
    void displayGameStats(QPainter& painter);

private slots:
    // Button click slots
    void on_pushButtonEndTurn_clicked();
    void on_pushButtonMCTS_clicked();
    void on_pushButtonSaveGame_clicked();
    void on_pushButtonLoadSave_clicked();

private:
    Ui::GameStatsWidgetClass ui;
    TwixtGame& game;
    BoardWidget& boardWidget;
    std::string savePath;

    // Drawing functions
    void drawCurrentPlayer(QPainter& painter);
    void drawPlayerStats(QPainter& painter, const Player& player, int xOffset);

    // Save game functions
    std::string generateSaveFileName() const;
    void saveBoardState(std::ofstream& saveFile) const;
    void savePegState(std::ofstream& saveFile, const Cell& cell) const;
    void saveGameStats(std::ofstream& saveFile) const;
    void saveLinkState(std::ofstream& saveFile, const Cell& cell, std::unordered_set<Link*>& alreadySaved) const;
};
