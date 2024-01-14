#pragma once

#include "Board.h"
#include "Player.h"
#include <fstream>
#include <regex>

namespace twixt {

    class TwixtGame {
    public:
        // Constructors and destructor
        TwixtGame(size_t boardSize = 12, uint8_t numOfPieces = 50, uint32_t numOfMCTSSimulations = 10000);
        ~TwixtGame();
        TwixtGame(TwixtGame& other);

        // Getter functions
        Board& getBoard();
        uint32_t getNumOfMCTSSimulations();
        Player& getCurrentPlayer();
        Player& getFirstPlayer();
        Player& getSecondPlayer();

        // Setter functions
        void setCurrentPlayer(Color color);

        // Game state manipulation functions
        void switchPlayer();
        void goToNextState(const Action& action);

        // Helper functions for AI
        ActionSet getValidActions();
        ActionSet getValidPegActions();
        ActionSet getValidLinkActions();
        ActionSet getValidLinkActionsImproved(Position positionOfLastPegPlaced);
        ActionSet getValidImaginaryLinkActions(Position positionOfImaginaryPeg);

        // Game status functions
        bool isGameOver();
        bool isDraw();
        bool currentPlayerWon();

    private:
        // Member variables
        Board board;
        Player firstPlayer;
        Player secondPlayer;
        Color currentPlayer;
        uint32_t numOfMCTSSimulations;
    };
}
