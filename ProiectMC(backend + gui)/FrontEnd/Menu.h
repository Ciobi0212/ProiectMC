#pragma once

#include <QWidget>
#include "ui_Menu.h"
#include "FrontEnd.h"

class Menu : public QMainWindow {
    Q_OBJECT

public:
    // Constructors and destructor
    Menu(QMainWindow* parent = nullptr);
    ~Menu();

private slots:
    // Button click slot
    void on_pushButtonPlay_clicked();

private:
    Ui::MenuClass ui;
};
