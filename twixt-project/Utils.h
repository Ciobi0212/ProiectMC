#pragma once

#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <random>

// Enumeration for player colors
enum class Color { RED, BLUE, NONE };

// Enumeration for base types
enum class BaseType { VERTICAL, HORIZONTAL };

// Type representing a position on the board
template <typename T = std::size_t>
using Position = std::pair<T, T>;

// Hash function for a position
template <typename T = std::size_t>
struct PositionHash {
    std::size_t operator()(const Position<T>& pos) const {
        return std::hash<T>()(pos.first) ^ std::hash<T>()(pos.second);
    }
};

// Enumeration for different types of actions
enum class ActionType { PLACE_PEG, PLACE_LINK, NONE };

// Type representing an action with two positions
template <typename T = std::size_t, typename ActionType = ActionType>
using Action = std::tuple<ActionType, Position<T>, Position<T>>;

// Hash function for a tuple of positions using PositionHash
template <typename T = std::size_t>
struct PositionsTupleHash {
    template <typename U = T>
    std::size_t operator()(const U& t) const {
        std::size_t hashValue = 0;
        for (const auto& pos : t) {
            hashValue ^= PositionHash<T>()(pos);
        }
        return hashValue;
    }
};

// Hash function for the Action type using PositionsTupleHash for positions
template <typename T = std::size_t, typename ActionType = ActionType>
struct ActionHash {
    std::size_t operator()(const Action<T>& action) const {
        ActionType actionType = std::get<0>(action);
        Position<T> position1 = std::get<1>(action);
        Position<T> position2 = std::get<2>(action);
        return static_cast<std::size_t>(actionType) ^ PositionHash<T>()(position1) ^ PositionHash<T>()(position2);
    }
};

// Set of unique actions with custom hash function
template <typename T = std::size_t, typename ActionType = ActionType>
using ActionSet = std::unordered_set<Action<T, ActionType>, ActionHash<T>>;

//Function to extract a random action from a set of actions
template <typename T = std::size_t, typename ActionType = ActionType>
Action<T, ActionType> extractRandomAction(ActionSet<T, ActionType>& actions, std::mt19937& gen);

//Function to return a random index
template <typename T = std::size_t>
T randomIndex(T size, std::mt19937& gen);


