#include "Menu.h"

Menu::Menu(QMainWindow *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Menu::~Menu()
{}

void Menu::on_pushButtonPlay_clicked() {
	size_t boardSize = ui.boardSizeComboBox->currentText().toULongLong();
	uint8_t numOfPieces = ui.numbOfPieceComboBox->currentText().toUInt();
	uint32_t numOfMCTSSimulations = ui.MCTSComboBox->currentText().toUInt();
	
	TwixtGame* game = new TwixtGame{ boardSize, numOfPieces, numOfMCTSSimulations };
	FrontEnd* frontEnd = new FrontEnd{ *game };
	this->close();
	frontEnd->show();
}