#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

const uint_fast16_t WIDTH = 720, HEIGHT = 720;

class ClickablePointGridWidget : public QWidget {
public:
    ClickablePointGridWidget(const uint16_t& gridSize, const uint16_t& cellSize, QWidget *parent = nullptr) : QWidget(parent) {
        setMouseTracking(true); // Enable mouse move events
        this->gridSize = gridSize;
        this->cellSize = cellSize;
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);

        QPainter painter(this);

        // Set the pen color and size
        painter.setPen(QPen(Qt::black, 1));

        // Draw the grid of points
        for (int i = 0; i < gridSize; ++i) {
            for (int j = 0; j < gridSize; ++j) {
                if(!((i == 0 and j == 0) || (i == 0 and j == gridSize - 1) || (i == gridSize - 1 and j == 0) || (i == gridSize - 1 and j == gridSize - 1))){
                uint16_t x = i * cellSize + cellSize/2;
                uint16_t y = j * cellSize + cellSize/2;
                painter.drawEllipse(x, y, 10, 10);
                }
            }
        }

        // Draw the line separating each base
        painter.setPen(QPen(Qt::red,3));
        painter.drawLine(cellSize+10, cellSize, WIDTH-cellSize, cellSize);
        painter.drawLine(cellSize+10, WIDTH-cellSize, WIDTH-cellSize-10, WIDTH-cellSize);

        painter.setPen(QPen(Qt::blue,3));
        painter.drawLine(cellSize, cellSize, cellSize, WIDTH-cellSize);
        painter.drawLine(WIDTH-cellSize, cellSize, WIDTH-cellSize, WIDTH-cellSize);
    }


    void mousePressEvent(QMouseEvent *event) override {
        int clickedX = event->x();
        int clickedY = event->y();

        // Determine which point was clicked
        int clickedRow = clickedX / cellSize;
        int clickedCol = clickedY / cellSize;

        qDebug() << "Clicked on point (" << clickedRow << ", " << clickedCol << ")";
    }

private:
    int gridSize;
    int cellSize;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ClickablePointGridWidget* widget = new ClickablePointGridWidget(24, WIDTH/24);
    widget->resize(WIDTH, HEIGHT);
    widget->show();

    return app.exec();
}

