#pragma once

#include <string>
#include <vector>

#include <QColor> 
#include "Peg.h"
#include "Link.h"
#include "Board.h"

namespace twixt {

    class Player {
    public:
        // Constructors and destructor
        Player();
        Player(const std::string& name, Color color, BaseType baseType,
            uint8_t numOfPegsLeft = 50, uint8_t numOfLinksLeft = 50, QColor qcolor = Qt::white,
            bool placedPeg = false, Peg* selectedPeg = nullptr);
        Player(const Player& other);
        ~Player();

        // Assignment operator
        Player& operator=(const Player& other);

        // Getters
        const std::string& getName() const;
        uint8_t getNumOfPegsLeft() const;
        uint8_t getNumOfLinksLeft() const;
        Color getColor() const;
        QColor getQColor() const;
        Peg* getSelectedPeg() const;
        bool getPlacedPeg() const;
        ActionSet<>& getValidPegPositions();

        // Setters
        void setName(const std::string& name);
        void setColor(Color color);
        void setQColor(QColor qcolor);
        void setNumOfPegsLeft(uint8_t numOfPegsLeft);
        void setNumOfLinksLeft(uint8_t numOfLinksLeft);
        void setPlacedPeg(bool status);
        void setSelectedPeg(Peg* selectedPeg);
        void resetPlayer();

        // Board-related functions
        void placePegOnBoard(Board& board, const Position<>& pos);
        void placeLinkOnBoard(Board& board, const Position<>& pos1, const Position<>& pos2);
        void removeLinkFromBoard(Board& board, Link* linkToRemove);

        // Validation functions
        bool linkCanBePlaced(Board& board, const Position<>& pos1, const Position<>& pos2) const;
        bool imaginaryLinkCanBePlaced(Board& board, const Position<>& pos1, const Position<>& pos2) const;
        bool pegCanBePlaced(Board& board, const Position<>& pos) const;
        bool checkLinkOverlapImproved(Board& board, const Position<>& pos1, const Position<>& pos2) const;
        bool checkForWin(Board& board) const;

        // Valid peg move handling
        void initValidPegPositions(Board& board);
        void eraseValidPegPosition(const Action<>& action);

    private:
        // Member variables
        std::string m_name;
        Color m_color;
        uint8_t m_numOfPegsLeft;
        uint8_t m_numOfLinksLeft;
        QColor m_qcolor;
        BaseType m_baseType;
        bool m_placedPeg{ false };
        Peg* m_selectedPeg{ nullptr };

        // Useful for MCTS
        ActionSet<> m_validPegPositions;
    };
}
