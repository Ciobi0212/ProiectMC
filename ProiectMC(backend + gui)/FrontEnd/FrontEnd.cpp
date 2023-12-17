#include "FrontEnd.h"

FrontEnd::FrontEnd(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(widthRes, heightRes);
	setWindowTitle("Twixt");
	boardSize = game.getBoard().getSize();
	radius = 5;
	cellSize = widthRes / boardSize;
	isDrawingLink = false;
	setMouseTracking(true);

	//set screenCoords for all cells
	for (size_t row = 0; row < boardSize; ++row) {
		for (size_t col = 0; col < boardSize; ++col) {
			game.getBoard()[{row, col}].setPositionOnScreen(QPoint(col * cellSize + cellSize / 2 - radius, row * cellSize + cellSize / 2 - radius));
		}
	}


}

FrontEnd::~FrontEnd()
{}

void FrontEnd::drawBoard(QPainter& painter)
{
	Board& board = game.getBoard();
	Player& currentPlayer = game.getCurrentPlayer();

	size_t boardSize = board.getSize();


	for (size_t row = 0; row < boardSize; ++row) {
		for (size_t col = 0; col < boardSize; ++col) {
			painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
			Cell& cell = board[{row, col}];

			if (isCornerCell(row, col, boardSize)) {
				continue;
			}

			drawCellContent(painter, cell);
		}
	}
}

//void FrontEnd::drawPegsAndLinks(QPainter& painter)
//{
//    Board& board = game.getBoard();
//    Player& currentPlayer = game.getCurrentPlayer();
//
//    size_t boardSize = board.getSize();
//    size_t cellSize = widthRes / boardSize;
//    size_t radius = 5;
//
//    for (size_t row = 0; row < boardSize; ++row) {
//        for (size_t col = 0; col < boardSize; ++col) {
//            painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
//
//            if (isCornerCell(row, col, boardSize)) {
//                continue;
//            }
//
//            drawCellContent(painter, board, currentPlayer, row, col);
//        }
//    }
//}
//
void FrontEnd::drawCellContent(QPainter& painter, Cell& cell)
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

void FrontEnd::drawEmptyCell(QPainter& painter, Cell& cell)
{
	painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
	size_t centerX = cell.getPositionOnScreen().x();
	size_t centerY = cell.getPositionOnScreen().y();
	painter.drawEllipse(centerX, centerY, radius * 2, radius * 2);
}

void FrontEnd::drawPeg(QPainter& painter, Peg& peg)
{
	painter.setBrush(QBrush(peg.getQColor(), Qt::SolidPattern));
	size_t centerX = peg.getPositionOnScreen().x();
	size_t centerY = peg.getPositionOnScreen().y();
	painter.drawEllipse(centerX, centerY, radius * 2, radius * 2);
}




void FrontEnd::drawLinksOfCell(QPainter& painter, const Cell& cell)
{
	QColor linkColor = cell.getPeg().getQColor();
	painter.setPen(QPen(linkColor, 3, Qt::SolidLine, Qt::RoundCap));
	for (Link* link : cell.getLinks()) {
		auto [yStart, xStart] = link->getP1().getPosition();
		auto [yEnd, xEnd] = link->getP2().getPosition();
		painter.drawLine(xStart * cellSize + cellSize / 2, yStart * cellSize + cellSize / 2, xEnd * cellSize + cellSize / 2, yEnd * cellSize + cellSize / 2);
	}
}

//
//void FrontEnd::drawEmptyCell(QPainter& painter, size_t row, size_t col)
//{
//    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
//    size_t centerX = col * cellSize + cellSize / 2 - radius;
//    size_t centerY = row * cellSize + cellSize / 2 - radius;
//    painter.drawEllipse(centerX, centerY, radius * 2, radius * 2);
//}
//
//void FrontEnd::drawPeg(QPainter& painter, size_t row, size_t col)
//{
//    size_t centerX = col * cellSize + cellSize / 2 - radius;
//    size_t centerY = row * cellSize + cellSize / 2 - radius;
//    painter.drawEllipse(centerX, centerY, radius * 2, radius * 2);
//}
//
//
//void FrontEnd::setPegColor(QPainter& painter, Color color)
//{
//    if (color == Color::RED) {
//		painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
//    }
//    else {
//		painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
//    }
//}
//
//void FrontEnd::setLinkColor(QPainter& painter, Color color)
//{
//    if (color == Color::RED) {
//        painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap));
//    }
//    else if (color == Color::BLUE) {
//        painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap));
//    }
//    else if (color == Color::RED_TRANSPARENT) {
//        QColor transparentRed = QColor(Qt::red);
//        transparentRed.setAlpha(10);
//        painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap));
//    }
//    else if (color == Color::BLUE_TRANSPARENT) {
//        QColor transparentBlue = QColor(Qt::blue);
//        transparentBlue.setAlpha(10);
//        painter.setPen(QPen(transparentBlue, 3, Qt::SolidLine, Qt::RoundCap));
//    }
//}
//
//void FrontEnd::drawLinks(QPainter& painter, const Board& board, size_t row, size_t col)
//{
    
//}
//
bool FrontEnd::isCornerCell(size_t row, size_t col, size_t boardSize)
{
	return (row == 0 && col == 0) || (row == 0 && col == boardSize - 1) ||
		(row == boardSize - 1 && col == 0) || (row == boardSize - 1 && col == boardSize - 1);
}
bool FrontEnd::isClickOnCell(QPoint click, Cell& cell)
{
	QPoint cellPos = cell.getPositionOnScreen();
	size_t centerX = cellPos.x();
	size_t centerY = cellPos.y();
	size_t distance = sqrt(pow(click.x() - centerX, 2) + pow(click.y() - centerY, 2));
	return distance <= radius*2;
}
bool FrontEnd::isClickOnLink(QPoint click, Link* link)
{
	//use screnn coordinates
	auto [xStart, yStart] = link->getP1().getPositionOnScreen();
	auto [xEnd, yEnd] = link->getP2().getPositionOnScreen();
	double slope = static_cast<double>(yEnd - yStart) / static_cast<double>(xEnd - xStart);
	double expectedY = slope * static_cast<double>(click.x() - xStart) + yStart;
	if (abs(expectedY - click.y()) < 10) {
		return true;
	}
}
void FrontEnd::handleCellClick(const Position& pos, Player& currentPlayer, Board& board)
{
	if (board[pos].hasPeg()) {
		if (board[pos].getPeg().getColor() == currentPlayer.getColor()) {
			isDrawingLink = true;
		}
	}
		
	else {
		if (currentPlayer.pegCanBePlaced(board, pos)) {
			currentPlayer.placePegOnBoard(board, pos);
			repaint();
			game.switchPlayer();
		}
	}

}
//
void FrontEnd::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);


	drawBoard(painter);
	if (isDrawingLink) {
		painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
		painter.drawLine(startPoint, endPoint);
	}
}
void FrontEnd::mouseMoveEvent(QMouseEvent* event) {
	if (isDrawingLink) {
		endPoint = event->pos();
		repaint();
	}
}
//
//void FrontEnd::mouseMoveEvent(QMouseEvent* event)
//{
//	Board& board = game.getBoard();
//	Player& currentPlayer = game.getCurrentPlayer();
//	QPoint mousePos = event->pos();
//	uint8_t alowedDistance = 10;
//
//    //get the cooord of the cell we are on 
//	size_t xCell = mousePos.y() / cellSize;
//	size_t yCell = mousePos.x() / cellSize;
//   
//}
//
void FrontEnd::mousePressEvent(QMouseEvent* event)
{
    Board& board = game.getBoard();
    Player& currentPlayer = game.getCurrentPlayer();

    QPoint mousePos = event->pos();
	startPoint = mousePos;
	endPoint = mousePos;
    //iterate over cells and check if the click was on a cell
	for (size_t row = 0; row < board.getSize(); row++) {
		for (size_t col = 0; col < board.getSize(); col++) {
			Cell& currentCell = board[{row, col}];
			if (isClickOnCell(mousePos, currentCell)) {
				handleCellClick({row,col}, currentPlayer, board);
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
					currentPlayer.removeLinkFromBoard(board, link);
					repaint();
					return;
				}
			}
		}
	}
}

    //// Get coordinates of the center of the circle
    //size_t xOfCircle = yCell * cellSize + cellSize / 2 - radius;
    //size_t yOfCircle = xCell * cellSize + cellSize / 2 - radius;

    //Cell& cell = board[{xCell, yCell}];

    //
    //if (!cell.hasPeg() && currentPlayer.pegCanBePlaced(board, { xCell, yCell })) {
    //    // Check if the click was on the circle
    //    if (sqrt(pow(mousePos.x() - xOfCircle, 2) + pow(mousePos.y() - yOfCircle, 2)) > radius * 2) {
    //        return;
    //    }
    //    currentPlayer.placePegOnBoard(board, { xCell, yCell });
    //    repaint();
    //    if (currentPlayer.checkForWin(board)) {
    //        QMessageBox msgBox;
    //        msgBox.setWindowTitle("Game Over");
    //        // Set text to "Player" currentPlayer.getName() "has won the game"
    //        QString content = "Player " + QString::fromStdString(currentPlayer.getName()) + " has won the game";
    //        msgBox.setText(content);
    //        msgBox.exec();
    //    }
    //    game.switchPlayer();
    //}

    //else {

    //    int alowedDistance = 20;
    //    for (Link* link : board[{xCell, yCell}].getLinks()) {
    //        //determine the closest link to the mouse
    //        auto [yStart, xStart] = link->getP1().getPosition();
    //        auto [yEnd, xEnd] = link->getP2().getPosition();
    //        
    //        // Translate the link coords to screen coords
    //        yStart = yStart * cellSize + cellSize / 2.0 - radius;
    //        xStart = xStart * cellSize + cellSize / 2.0 - radius;
    //        yEnd = yEnd * cellSize + cellSize / 2.0 - radius;
    //        xEnd = xEnd * cellSize + cellSize / 2.0 - radius;

    //        // Ensure floating-point division for the slope calculation
           

    //    }
    //}


void FrontEnd::mouseReleaseEvent(QMouseEvent* event)
{
	endPoint = event->pos();
	isDrawingLink = false;
	//manage link
}
