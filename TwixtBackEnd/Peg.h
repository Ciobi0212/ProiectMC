#pragma once
#include <utility>

namespace twixt {
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
}

