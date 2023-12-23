#pragma once
#include "TwixtGame.h"
#include <random>
class MonteCarloTreeSearchNode {
public:
	MonteCarloTreeSearchNode(TwixtGame state, MonteCarloTreeSearchNode* parent = nullptr, Action parent_action = Action(ActionType::NONE, { -1,-1 }, { -1, -1 }));
	~MonteCarloTreeSearchNode();
	int wins_minus_loses();
	MonteCarloTreeSearchNode* expand();
	bool is_terminal_node();
	int rollout();
	void backpropagate(int result);
	bool is_fully_expanded();
	MonteCarloTreeSearchNode* best_child(double c_param);
	MonteCarloTreeSearchNode* _tree_policy();
	Action get_best_action();
	
private:
	TwixtGame state;
	MonteCarloTreeSearchNode* parent;
	Action parent_action;
	std::vector<MonteCarloTreeSearchNode*> children;
	ActionSet untried_actions;
	int wins;
	int losses;
	double visits;
	std::random_device rd;
	std::mt19937 eng{rd()};
};

