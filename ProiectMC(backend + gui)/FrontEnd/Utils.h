#pragma once

#include <unordered_set>
#include <unordered_map>
#include <tuple>

// Enumeration for player colors
enum class Color { RED, BLUE, NONE };

// Enumeration for base types
enum class BaseType {
    VERTICAL, HORIZONTAL
};

// Type representing a position on the board
using Position = std::pair<std::size_t, std::size_t>;

// Hash function for a position
struct PositionHash {
    std::size_t operator()(const Position& pos) const {
        return std::hash<std::size_t>()(pos.first) ^ std::hash<std::size_t>()(pos.second);
    }
};

// Enumeration for different types of actions
enum class ActionType {
    PLACE_PEG, PLACE_LINK, NONE
};

// Type representing an action with two positions
using Action = std::tuple<ActionType, Position, Position>;

// Hash function for a tuple of positions using PositionHash
struct PositionsTupleHash {
    template <typename T>
    std::size_t operator()(const T& t) const {
        std::size_t hashValue = 0;
        for (const auto& pos : t) {
            hashValue ^= PositionHash()(pos);
        }
        return hashValue;
    }
};

// Hash function for the Action type using PositionsTupleHash for positions
struct ActionHash {
    std::size_t operator()(const Action& action) const {
        ActionType actionType = std::get<0>(action);
        Position position1 = std::get<1>(action);
        Position position2 = std::get<2>(action);
        return static_cast<std::size_t>(actionType) ^ PositionHash{}(position1) ^ PositionHash{}(position2);
    }
};

// Set of unique actions with custom hash function
using ActionSet = std::unordered_set<Action, ActionHash>;
