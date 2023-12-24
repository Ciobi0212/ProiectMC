#pragma once
#include "TwixtGame.h"
#include <random>
class MonteCarloTreeSearchNode {
public:
	MonteCarloTreeSearchNode(TwixtGame state, MonteCarloTreeSearchNode* parent = nullptr, Action parent_action = Action(ActionType::NONE, { -1,-1 }, { -1, -1 }));
	~MonteCarloTreeSearchNode();
	MonteCarloTreeSearchNode* select();
	MonteCarloTreeSearchNode* expand();
	double rollout();
	void backpropagate(double result);
	double getUCBValue(MonteCarloTreeSearchNode* node, double exploration_parameter = 1.414);
	bool is_terminal_node();
	

	TwixtGame state;
	MonteCarloTreeSearchNode* parent;
	Action parent_action;
	std::vector<MonteCarloTreeSearchNode*> children;
	ActionSet untried_actions;
	double wins;
	double visits;
	std::random_device rd;
	std::mt19937 eng{rd()};
};

class MCTS {
public:
	MCTS(TwixtGame state);
	~MCTS();
	void dealocateTree(MonteCarloTreeSearchNode* node);
	Action best_action(uint16_t simulations_number);
//private:
	MonteCarloTreeSearchNode* root;
};

