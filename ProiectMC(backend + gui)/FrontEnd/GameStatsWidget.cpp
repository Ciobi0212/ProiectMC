#include "GameStatsWidget.h"
#include <fstream>
#include <ctime>
#include <QFileDialog>

GameStatsWidget::GameStatsWidget(TwixtGame& game, BoardWidget& boardWidget, QWidget* parent)
    : QWidget(parent), game{ game }, boardWidget{ boardWidget }, savePath{ "SavedGames" }
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
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    drawCurrentPlayer(painter);
    drawPlayerStats(painter, game.getFirstPlayer(), 200);
    drawPlayerStats(painter, game.getSecondPlayer(), 400);
}

void GameStatsWidget::drawCurrentPlayer(QPainter& painter)
{
    painter.drawText(10, 20, "Current player's turn: ");
    Color currentPlayerColor = game.getCurrentPlayer().getColor();
    QColor currentPlayerQColor = (currentPlayerColor == Color::RED) ? QColor(255, 0, 0) : QColor(0, 0, 255);
    painter.setPen(currentPlayerQColor);
    painter.drawText(10, 40, (currentPlayerColor == Color::RED) ? "Red" : "Blue");
}

void GameStatsWidget::drawPlayerStats(QPainter& painter, const Player& player, int xOffset)
{
    QColor playerColor = (player.getColor() == Color::RED) ? QColor(255, 0, 0) : QColor(0, 0, 255);
    painter.setPen(playerColor);

    painter.drawText(xOffset, 20, "Number of pegs: ");
    painter.drawText(xOffset + 130, 20, QString::number(player.getNumOfPegsLeft()));

    painter.drawText(xOffset, 40, "Number of links: ");
    painter.drawText(xOffset + 130, 40, QString::number(player.getNumOfLinksLeft()));
}

void GameStatsWidget::on_pushButtonEndTurn_clicked()
{
    game.switchPlayer();
    boardWidget.repaint();
    repaint();
}

void GameStatsWidget::on_pushButtonMCTS_clicked()
{
    MCTS mcts(game);
    boardWidget.setRecommendedAction(mcts.best_action(10000));
    boardWidget.repaint();
}

void GameStatsWidget::on_pushButtonSaveGame_clicked()
{
    std::string saveFileName = generateSaveFileName();
    std::ofstream saveFile(savePath + "\\" + saveFileName);

    saveFile << game.getBoard().getSize() << "\n";
    saveBoardState(saveFile);

    saveFile << "CurrentPlayer " << ((game.getCurrentPlayer().getColor() == Color::RED) ? "RED" : "BLUE") << "\n";
    saveFile << "CanPlacePeg " << !game.getCurrentPlayer().getPlacedPeg();

    saveFile.close();
}

std::string GameStatsWidget::generateSaveFileName() const
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return std::to_string(1900 + ltm->tm_year) + "_" + std::to_string(1 + ltm->tm_mon) + "_" +
        std::to_string(ltm->tm_mday) + "_" + std::to_string(ltm->tm_hour) + "_" +
        std::to_string(ltm->tm_min) + "_" + std::to_string(ltm->tm_sec) + ".txt";
}

void GameStatsWidget::saveBoardState(std::ofstream& saveFile) const
{
    const Board& board = game.getBoard();
    for (size_t i = 0; i < board.getSize(); i++) {
        for (size_t j = 0; j < board.getSize(); j++) {
            savePegState(saveFile, board[{i, j}]);
        }
    }

    std::unordered_set<Link*> alreadySaved;
    for (size_t i = 0; i < board.getSize(); i++) {
        for (size_t j = 0; j < board.getSize(); j++) {
            saveLinkState(saveFile, board[{i, j}], alreadySaved);
        }
    }
}

void GameStatsWidget::savePegState(std::ofstream& saveFile, const Cell& cell) const
{
    if (cell.hasPeg()) {
        const Peg& peg = cell.getPeg();
        std::string playerColor = (peg.getColor() == Color::RED) ? "RED" : "BLUE";
        saveFile << playerColor << " PEG " << cell.getPeg().getPosition().first << " " << cell.getPeg().getPosition().second << "\n";
    }
}

void GameStatsWidget::saveLinkState(std::ofstream& saveFile, const Cell& cell,
    std::unordered_set<Link*>& alreadySaved) const
{
    if (cell.hasLinks()) {
        for (Link* link : cell.getLinks()) {
            if (alreadySaved.find(link) == alreadySaved.end()) {
                Position firstPeg = link->getP1().getPosition();
                Position secondPeg = link->getP2().getPosition();
                std::string playerColor = (link->getColor() == Color::RED) ? "RED" : "BLUE";
                saveFile << playerColor << " LINK " << firstPeg.first << " " << firstPeg.second << " " <<
                    secondPeg.first << " " << secondPeg.second << "\n";
                alreadySaved.insert(link);
            }
        }
    }
}

void GameStatsWidget::on_pushButtonLoadSave_clicked()
{
    QString savePath = "SavedGames";
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), savePath, tr("Text files (*.txt)"));
    boardWidget.loadSave(fileName.toStdString());
    boardWidget.repaint();
    repaint();
}
