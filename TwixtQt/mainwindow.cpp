#include "mainwindow.h"
#include "./ui_mainwindow.h"
const uint_fast16_t WIDTH = 800, HEIGHT = 600;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(WIDTH, HEIGHT);
    resize(800,800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

