#pragma once
#include "TwixtGame.h"
#include <random>
#include <thread>
class MonteCarloTreeSearchNode {
public:
	MonteCarloTreeSearchNode(TwixtGame& state, std::mt19937& eng, MonteCarloTreeSearchNode* parent = nullptr, Action parent_action = Action(ActionType::NONE, { -1,-1 }, { -1, -1 }));
	~MonteCarloTreeSearchNode();
	MonteCarloTreeSearchNode* select(TwixtGame& state);
	MonteCarloTreeSearchNode* expand(TwixtGame& state);
	double rollout(TwixtGame& state);
	void backpropagate(double result);
	double getUCBValue(MonteCarloTreeSearchNode* node, double exploration_parameter = 1.414);
	bool is_terminal_node();
	

	MonteCarloTreeSearchNode* parent;
	Color playerTurn;
	Action parent_action;
	std::vector<MonteCarloTreeSearchNode*> children;
	ActionSet untried_actions;
	double wins;
	double visits;
	std::mt19937& eng;
};

class MCTS {
public:
	MCTS(TwixtGame& state);
	~MCTS();
	void dealocateTree(MonteCarloTreeSearchNode* node);
	Action best_action(uint16_t simulations_number);
//private:
	MonteCarloTreeSearchNode* root;
	TwixtGame original_state;
	std::random_device rd;
	std::mt19937 eng;
};

