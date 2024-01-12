#include "BoardWidget.h"

BoardWidget::BoardWidget(TwixtGame& game, QWidget* parent)
    : QWidget{ parent }, game{ game }
{
    ui.setupUi(this);
    setFixedSize(boardWidth, boardHeight);
    setWindowTitle("Twixt");

    boardSize = game.getBoard().getSize();
    cellSize = boardWidth / boardSize;

    setScreenCoordsForCells();

    recommandedAction = { ActionType::NONE, {0,0}, {0,0} };
}

BoardWidget::~BoardWidget() = default;

void BoardWidget::drawBoard(QPainter& painter)
{
    Board& board = game.getBoard();

    for (size_t row = 0; row < boardSize; ++row) {
        for (size_t col = 0; col < boardSize; ++col) {
            const Cell& cell = board[{row, col}];
            if (!isCornerCell(row, col, boardSize)) {
                painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
                drawCellContent(painter, cell);
            }
        }
    }

    drawBaseDelimitators(painter);
    drawRecommandation(painter);
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
    painter.setBrush((&peg == game.getCurrentPlayer().getSelectedPeg()) ? QBrush(Qt::green, Qt::SolidPattern) : QBrush(peg.getQColor(), Qt::SolidPattern));
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
        painter.drawLine(xStart * cellSize + cellSize / 2, yStart * cellSize + cellSize / 2, xEnd * cellSize + cellSize / 2, yEnd * cellSize + cellSize / 2);
    }
}

bool BoardWidget::isCornerCell(size_t row, size_t col, size_t boardSize) const
{
    return (row == 0 && col == 0) || (row == 0 && col == boardSize - 1) ||
        (row == boardSize - 1 && col == 0) || (row == boardSize - 1 && col == boardSize - 1);
}

bool BoardWidget::isClickOnCell(QPoint click, Cell& cell) const
{
    QPoint cellPos = cell.getPositionOnScreen();
    size_t distance = sqrt(pow(click.x() - cellPos.x(), 2) + pow(click.y() - cellPos.y(), 2));
    return distance <= radius * 2;
}

bool BoardWidget::isClickOnLink(QPoint click, Link* link) const
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

    return distance < 8.0; // Threshold
}

void BoardWidget::setScreenCoordsForCells()
{
    for (size_t row = 0; row < boardSize; ++row) {
        for (size_t col = 0; col < boardSize; ++col) {
            auto& currentCell = game.getBoard()[{row, col}];
            currentCell.setPositionOnScreen(QPoint(col * cellSize + cellSize / 2 - radius, row * cellSize + cellSize / 2 - radius));
        }
    }
}

void BoardWidget::handleCellClick(const Position& pos, Player& currentPlayer, Board& board)
{
    auto& currentCell = board[pos];
    if (!currentCell.hasPeg()) { // Cell is empty
        if (currentPlayer.pegCanBePlaced(board, pos)) {
            currentPlayer.placePegOnBoard(board, pos);
            repaint();
        }
    }
    else if (currentCell.getPeg().getColor() == currentPlayer.getColor()) { // Current player clicked on one of his pegs
        auto selectedPeg = currentPlayer.getSelectedPeg();
        if (selectedPeg == nullptr) {
            currentPlayer.setSelectedPeg(&currentCell.getPeg());
            repaint();
        }
        else if (selectedPeg != &currentCell.getPeg()) {
            Position posPeg1 = selectedPeg->getPosition();
            Position posPeg2 = currentCell.getPeg().getPosition();
            if (currentPlayer.linkCanBePlaced(board, posPeg1, posPeg2)) {
                currentPlayer.placeLinkOnBoard(board, posPeg1, posPeg2);
                if (currentPlayer.checkForWin(board)) {
                    winMessage(currentPlayer);
                    exit(0);
                }
            }
            currentPlayer.setSelectedPeg(nullptr);
            repaint();
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

void BoardWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBoard(painter);
}

void BoardWidget::drawRecommandation(QPainter& painter)
{
    if (std::get<0>(recommandedAction) != ActionType::NONE) {
        auto& board = game.getBoard();
        auto& firstCell = board[std::get<1>(recommandedAction)];
        size_t centerX = firstCell.getPositionOnScreen().x();
        size_t centerY = firstCell.getPositionOnScreen().y();
        painter.setBrush(QBrush(Qt::cyan, Qt::SolidPattern));
        painter.drawEllipse(centerX, centerY, radius * 2, radius * 2);
    }
    recommandedAction = { ActionType::NONE, {0,0}, {0,0} };
}

void BoardWidget::mousePressEvent(QMouseEvent* event)
{
    auto& board = game.getBoard();
    auto& currentPlayer = game.getCurrentPlayer();
    QPoint mousePos = event->pos();

    // Iterate over cells and check if the click was on a cell
    for (size_t row = 0; row < board.getSize(); row++) {
        for (size_t col = 0; col < board.getSize(); col++) {
            auto& currentCell = board[{row, col}];
            if (isClickOnCell(mousePos, currentCell)) {
                handleCellClick({ row,col }, currentPlayer, board);
                return;
            }
        }
    }

    // Iterate over links and check if the click was on a link
    for (size_t row = 0; row < board.getSize(); row++) {
        for (size_t col = 0; col < board.getSize(); col++) {
            auto& currentCell = board[{row, col}];
            // Check if click was on a link
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
    msgBox.setText((player.getColor() == Color::RED) ? "Red player won!" : "Blue player won!");
    msgBox.exec();
}

void BoardWidget::setRecommendedAction(Action action)
{
    recommandedAction = action;
}

void BoardWidget::loadSave(const std::string& savedGamePath)
{
    std::ifstream savedGame(savedGamePath);
    if (!savedGame.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    savedGame >> line;
    if (std::stoul(line) != game.getBoard().getSize()) {
        QMessageBox msgBox;
        msgBox.setText("The save file does not match the current board size");
        msgBox.exec();
        return;
    }

    resetGame();
    game.getCurrentPlayer().setPlacedPeg(false);

    while (!savedGame.eof()) {
        std::getline(savedGame, line);
        std::regex regex("[^\\s]+");
        std::sregex_iterator words_begin(line.begin(), line.end(), regex), words_end;
        std::vector<std::string> tokens;
        std::for_each(words_begin, words_end, [&tokens](const std::smatch& m) { tokens.push_back(m.str()); });

        if (tokens.size() > 0) {
            if (tokens[0] == "RED") {
                game.setCurrentPlayer(Color::RED);
            }
            else if (tokens[0] == "BLUE") {
                game.setCurrentPlayer(Color::BLUE);
            }

            if (tokens[1] == "PEG") {
                Position pos = { std::stoul(tokens[2]), std::stoul(tokens[3]) };
                game.getCurrentPlayer().placePegOnBoard(game.getBoard(), pos);
                game.getCurrentPlayer().setPlacedPeg(false);
            }
            else if (tokens[1] == "LINK") {
                Position pos1 = { std::stoul(tokens[2]), std::stoul(tokens[3]) };
                Position pos2 = { std::stoul(tokens[4]), std::stoul(tokens[5]) };
                game.getCurrentPlayer().placeLinkOnBoard(game.getBoard(), pos1, pos2);
            }

            if (tokens[0] == "CurrentPlayer") {
                game.setCurrentPlayer((tokens[1] == "RED") ? Color::RED : Color::BLUE);
            }
            if (tokens[0] == "CanPlacePeg") {
                game.getCurrentPlayer().setPlacedPeg(tokens[1] == "0");
            }
        }
    }
}

void BoardWidget::resetGame()
{
    auto& board = game.getBoard();
    board.resetBoard();
    game.getFirstPlayer().resetPlayer();
    game.getSecondPlayer().resetPlayer();
    setScreenCoordsForCells();
}
