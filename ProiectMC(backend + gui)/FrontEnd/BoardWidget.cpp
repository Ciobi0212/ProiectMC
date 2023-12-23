#include "BoardWidget.h"

BoardWidget::BoardWidget(TwixtGame& game ,QWidget* parent)
	: QWidget{ parent }, game{ game }
{
	ui.setupUi(this);
	setFixedSize(boardWidth, boardHeight);
	boardSize = game.getBoard().getSize();
	cellSize = boardWidth / boardSize;

	//set screenCoords for all cells, account for the fact the widget is in the center of the window
	for (size_t row = 0; row < boardSize; ++row) {
		for (size_t col = 0; col < boardSize; ++col) {
			game.getBoard()[{row, col}].setPositionOnScreen(QPoint(col * cellSize + cellSize / 2 - radius, row * cellSize + cellSize / 2 - radius));
		}
	}


}

BoardWidget::~BoardWidget()
{}

void BoardWidget::drawBoard(QPainter& painter)
{
	Board& board = game.getBoard();
	Player& currentPlayer = game.getCurrentPlayer();

	size_t boardSize = board.getSize();

	for (size_t row = 0; row < boardSize; ++row) {
		for (size_t col = 0; col < boardSize; ++col) {
			painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
			const Cell& cell = board[{row, col}];

			if (isCornerCell(row, col, boardSize)) {
				continue;
			}

			drawCellContent(painter, cell);
		}
	}

	drawBaseDelimitators(painter);
}

void BoardWidget::drawBaseDelimitators(QPainter& painter)
{
	painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
	painter.drawLine(0, cellSize, width(), cellSize);
	painter.drawLine(0, height() - cellSize, width(), height() - cellSize);

	painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap));
	painter.drawLine(cellSize, 0, cellSize, height());
	painter.drawLine(width() - cellSize, 0, width() - cellSize, height());
}

void BoardWidget::drawCellContent(QPainter& painter, const Cell& cell)
{
	if (cell.hasPeg()) {
		drawPeg(painter, cell.getPeg());
		drawLinksOfCell(painter, cell);
	}
	else {
		drawEmptyCell(painter, cell);
	}

	//drawLinks(painter, cell);
}

void BoardWidget::drawEmptyCell(QPainter& painter, const Cell& cell)
{
	painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
	size_t centerX = cell.getPositionOnScreen().x();
	size_t centerY = cell.getPositionOnScreen().y();
	painter.drawEllipse(centerX, centerY, radius * 2, radius * 2);
}

void BoardWidget::drawPeg(QPainter& painter, Peg& peg)
{
	painter.setBrush(QBrush(peg.getQColor(), Qt::SolidPattern));
	size_t centerX = peg.getPositionOnScreen().x();
	size_t centerY = peg.getPositionOnScreen().y();
	painter.drawEllipse(centerX, centerY, radius * 2, radius * 2);
}




void BoardWidget::drawLinksOfCell(QPainter& painter, const Cell& cell)
{
	QColor linkColor = cell.getPeg().getQColor();
	painter.setPen(QPen(linkColor, 3, Qt::SolidLine, Qt::RoundCap));
	for (Link* link : cell.getLinks()) {
		auto [yStart, xStart] = link->getP1().getPosition();
		auto [yEnd, xEnd] = link->getP2().getPosition();

		painter.drawLine(xStart * cellSize + cellSize / 2,
			yStart * cellSize + cellSize / 2, xEnd * cellSize + cellSize / 2,
			yEnd * cellSize + cellSize / 2);
	}
}

bool BoardWidget::isCornerCell(size_t row, size_t col, size_t boardSize)
{
	return (row == 0 && col == 0) || (row == 0 && col == boardSize - 1) ||
		(row == boardSize - 1 && col == 0) || (row == boardSize - 1 && col == boardSize - 1);
}
bool BoardWidget::isClickOnCell(QPoint click, Cell& cell)
{
	QPoint cellPos = cell.getPositionOnScreen();
	size_t centerX = cellPos.x();
	size_t centerY = cellPos.y();
	size_t distance = sqrt(pow(click.x() - centerX, 2) + pow(click.y() - centerY, 2));
	return distance <= radius * 2;
}
bool BoardWidget::isClickOnLink(QPoint click, Link* link)
{
	auto [xStart, yStart] = link->getP1().getPositionOnScreen();
	auto [xEnd, yEnd] = link->getP2().getPositionOnScreen();


	size_t minX = std::min(xStart, xEnd);
	size_t minY = std::min(yStart, yEnd);
	size_t maxX = std::max(xStart, xEnd);
	size_t maxY = std::max(yStart, yEnd);

	if (click.x() < minX || click.x() > maxX || click.y() < minY || click.y() > maxY) {
		return false;
	}

	double A = yStart - yEnd;
	double B = xEnd - xStart;
	double C = xStart * yEnd - xEnd * yStart;

	double distance = std::abs(A * click.x() + B * click.y() + C) / std::sqrt(A * A + B * B);

	double threshold = 8.0; // seems to be good enough

	return distance < threshold;
}
void BoardWidget::handleCellClick(const Position& pos, Player& currentPlayer, Board& board)
{
	if (board[pos].hasPeg()) {
		if (board[pos].getPeg().getColor() == currentPlayer.getColor()) {
		}
	}

	else {
		if (currentPlayer.pegCanBePlaced(board, pos)) {
			currentPlayer.placePegOnBoard(board, pos);
			repaint();
			if (currentPlayer.checkForWin(board)) {
				winMessage(currentPlayer);
				exit(0);
			}
			game.switchPlayer();
		}
	}

}
void BoardWidget::handleLinkClick(Link* link, Player& currentPlayer, Board& board)
{
	if (currentPlayer.getColor() == link->getColor()) {
		currentPlayer.removeLinkFromBoard(board, link);
		repaint();
	}

}
//
void BoardWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);


	drawBoard(painter);
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
	Board& board = game.getBoard();
	Player& currentPlayer = game.getCurrentPlayer();

	QPoint mousePos = event->pos();

	//iterate over cells and check if the click was on a cell
	for (size_t row = 0; row < board.getSize(); row++) {
		for (size_t col = 0; col < board.getSize(); col++) {
			Cell& currentCell = board[{row, col}];
			if (isClickOnCell(mousePos, currentCell)) {
				handleCellClick({ row,col }, currentPlayer, board);
				return;
			}
		}
	}
	//iterate over links and check if the click was on a link
	for (size_t row = 0; row < board.getSize(); row++) {
		for (size_t col = 0; col < board.getSize(); col++) {
			Cell& currentCell = board[{row, col}];
			//check if click was on a link
			for (auto link : currentCell.getLinks()) {
				if (isClickOnLink(mousePos, link)) {
					handleLinkClick(link, currentPlayer, board);
					return;
				}
			}
		}
	}
}

void BoardWidget::winMessage(const Player& player)
{
	QMessageBox msgBox;
	if (player.getColor() == Color::RED)
		msgBox.setText("Red player won!");
	else
		msgBox.setText("Blue player won!");

	msgBox.exec();
}
