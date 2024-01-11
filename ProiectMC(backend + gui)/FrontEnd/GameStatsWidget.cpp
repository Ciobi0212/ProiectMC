#include "GameStatsWidget.h"

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
	
	painter.drawText(10, 20, "Current player's turn: ");
	if (game.getCurrentPlayer().getColor() == Color::RED)
	{
		painter.setPen(QColor(255, 0, 0));
		painter.drawText(10, 40, "Red");
	}
	else
	{
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

void GameStatsWidget::on_pushButtonSaveGame_clicked()
{
	std::string saveFileName = "";
	time_t now = time(0);
	tm* ltm = localtime(&now);
	saveFileName += std::to_string(1900 + ltm->tm_year) + "_" + std::to_string(1 + ltm->tm_mon) + "_" + std::to_string(ltm->tm_mday) + "_" + std::to_string(ltm->tm_hour) + "_" + std::to_string(ltm->tm_min) + "_" + std::to_string(ltm->tm_sec) + ".txt";
	
	std::ofstream saveFile(savePath + "\\" + saveFileName);
	Board& board = game.getBoard();
	size_t boardSize = board.getSize();
	saveFile << boardSize << "\n";
	
	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++)
		{
			if (board[{i,j}].hasPeg())
			{
				std::string playerColor = board[{i, j}].getColor() == Color::RED ? "RED" : "BLUE";
				saveFile << playerColor << " " << "PEG" << " " << i << " " << j << "\n";
			}
		}
	}

	std::unordered_set<Link*> alreadySaved = {};
	for (size_t i = 0; i < boardSize; i++)
	{
		for (size_t j = 0; j < boardSize; j++)
		{
			if (board[{i, j}].hasLinks())
			{
				std::unordered_set<Link*> links = board[{i, j}].getLinks();
				std::for_each(links.begin(), links.end(), [&saveFile, &alreadySaved](Link* link) {
					if (alreadySaved.find(link) == alreadySaved.end())
					{
						Position firstPeg = link->getP1().getPosition();
						Position secondPeg = link->getP2().getPosition();
						std::string playerColor = link->getColor() == Color::RED ? "RED" : "BLUE";
						saveFile << playerColor << " " << "LINK" << " " << firstPeg.first << " " << firstPeg.second << " " << secondPeg.first << " " << secondPeg.second << "\n";
						alreadySaved.insert(link);
					}
					});
			}
		}
	}

	saveFile << "CurrentPlayer ";
	saveFile << (game.getCurrentPlayer().getColor() == Color::RED ? "RED" : "BLUE") << "\n";
	saveFile << "CanPlacePeg ";
	saveFile << !game.getCurrentPlayer().getPlacedPeg();
	saveFile.close();
}

void GameStatsWidget::on_pushButtonLoadSave_clicked()
{
	QString savePath = "SavedGames";
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), savePath, tr("Text files (*.txt)"));
	boardWidget.loadSave(fileName.toStdString());
	boardWidget.repaint();
	repaint();
}
