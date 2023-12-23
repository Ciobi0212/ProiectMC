#pragma once
#include <utility>
#include <vector>
#include <unordered_set>
#include <queue>
#include <string>
#include <stdexcept>
#include "pch.h"

enum class Color { RED, BLUE, NONE };
using Position = std::pair<size_t, size_t>;

struct PositionHash {
    std::size_t operator()(const Position& pos) const {
        return std::hash<std::size_t>()(pos.first) ^ std::hash<std::size_t>()(pos.second);
    }
};

class __declspec(dllexport) Peg {
public:
    Peg();
    Peg(size_t rowOnBoard, size_t columnOnBoard, Color color);
    ~Peg();
    size_t getRowOnBoard() const;
    size_t getColumnOnBoard() const;
    Color getColor() const;
    void setRowOnBoard(uint16_t rowOnBoard);
    void setColumnOnBoard(uint16_t columnOnBoard);
    void setColor(Color color);
    bool operator==(const Peg& peg) const;
    Position getPosition() const;

private:
    size_t m_rowOnBoard;
    size_t m_columnOnBoard;
    Color m_color;
};

class __declspec(dllexport) Link {
public:
    Link(Peg& p1, Peg& p2, Color color);
    ~Link();
    Peg& getP1() const;
    Peg& getP2() const;
    Color getColor() const;
    void setColor(Color color);
    void setP1(Peg& p1);
    void setP2(Peg& p2);
    Peg& getOtherEnd(const Peg& peg) const;

private:
    Peg& m_p1;
    Peg& m_p2;
    Color m_color;
};

class __declspec(dllexport) Cell {
private:
    Peg* m_peg;
    std::unordered_set<Link*> m_links;
    Color m_color;

public:
    Cell();
    ~Cell();
    Color getColor() const;
    Peg& getPeg() const;
    std::unordered_set<Link*> getLinks() const;
    void setColor(Color color);
    void setPeg(Peg* peg);
    void addLink(Link* link);
    void removeLink(Link* link);
    bool hasPeg() const;
    bool hasLinks() const;

};

class __declspec(dllexport) Board {
public:
    Board(size_t BOARD_SIZE = 24);
    ~Board();

    void drawBoard();
    size_t getSize() const;

    using Position = std::pair<std::size_t, std::size_t>;
    struct PositionHash {
        std::size_t operator()(const Position& pos) const {
            return std::hash<std::size_t>()(pos.first) ^ std::hash<std::size_t>()(pos.second);
        }
    };

    bool isInBounds(const Position& pos) const;

    Cell& operator[](const Position& pos);
    const Cell& operator[](const Position& pos) const;

private:
    std::vector<std::vector<Cell>> m_board;
    size_t BOARD_SIZE;
};

enum class BaseType {
    VERTICAL, HORIZONTAL
};

class __declspec(dllexport) Player {
public:
    Player();
    Player(const std::string& name, Color color, BaseType baseType,
        uint8_t numPegs = 50, uint8_t numLinks = 50);

    ~Player();
    const std::string& getName() const;
    Color getColor() const;
    uint8_t getNumPegs() const;
    uint8_t getNumLinks() const;
    void setName(const std::string& name);
    void setColor(Color color);
    std::vector<std::reference_wrapper<Peg>> getPegs() const;
    std::vector<std::reference_wrapper<Link>> getLinks() const;
    //std::vector<Peg*> setPegs(const std::vector<Peg&>& pegs);
    //std::vector<Link*> setLinks(const std::vector<Link&>& links);

    void placePegOnBoard(Board& board, const Position& pos);
    void placeLinkOnBoard(Board& board, const Position& pos1, const Position& pos2);
    void removeLinkFromBoard(Board& board, Link* linkToRemove);
    void addPeg(Peg& peg);
    void addLink(Link& link);

    bool linkCanBePlaced(Board& board, const Position& pos1, const Position& pos2) const;
    bool pegCanBePlaced(Board& board, const Position& pos) const;
    bool checkLinkOverlap(Board& board, const Position& pos1, const Position& pos2) const;
    bool checkForWin(Board& board);




private:
    std::string m_name;
    Color m_color;
    BaseType m_baseType;
    uint8_t m_numPegs;
    uint8_t m_numLinks;
    std::vector<std::reference_wrapper<Peg>> m_pegs;
    std::vector<std::reference_wrapper<Link>> m_links;
};

class __declspec(dllexport) TwixtGame
{
public:
    TwixtGame();
    ~TwixtGame();
    Board& getBoard();
    void switchPlayer();
    Player& getCurrentPlayer();

private:
    Board board;
    Player firstPlayer;
    Player secondPlayer;
    Player* currentPlayer;

};
