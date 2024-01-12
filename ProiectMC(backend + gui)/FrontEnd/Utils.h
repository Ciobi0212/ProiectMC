#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <functional>

enum class Color { RED, BLUE, NONE };

enum class BaseType {
	VERTICAL, HORIZONTAL
};

using Position = std::pair<std::size_t, std::size_t>;
struct PositionHash {
	std::size_t operator()(const Position& pos) const {
		return std::hash<std::size_t>()(pos.first) ^ std::hash<std::size_t>()(pos.second);
	}
};

enum class ActionType {
	PLACE_PEG, PLACE_LINK, NONE
};
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
// Hash function for a pair of integers
// Hash function for the Action type
struct ActionHash {
	std::size_t operator()(const Action& action) const {
		ActionType actionType = std::get<0>(action);
		Position position1 = std::get<1>(action);
		Position position2 = std::get<2>(action);
		return static_cast<std::size_t>(actionType) ^ PositionHash {}(position1) ^ PositionHash {}(position2);
	}
};
using ActionSet = std::unordered_set<Action, ActionHash>;
