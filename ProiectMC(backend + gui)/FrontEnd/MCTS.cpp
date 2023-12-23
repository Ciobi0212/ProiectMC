//#include "MCTS.h"
//
//MonteCarloTreeSearchNode::MonteCarloTreeSearchNode(TwixtGame state, MonteCarloTreeSearchNode* parent, Action parent_action)
//{
//	this->state = state;
//	this->parent = parent;
//	this->parent_action = parent_action;
//	this->wins = 0;
//	this->losses = 0;
//	this->visits = 0;
//	this->untried_actions = state.getValidActions();
//}
//
//MonteCarloTreeSearchNode::~MonteCarloTreeSearchNode() = default;
//
//int MonteCarloTreeSearchNode::wins_minus_loses()
//{
//	return wins - losses;
//}
//
//MonteCarloTreeSearchNode* MonteCarloTreeSearchNode::expand()
//{
//	Action action = *untried_actions.begin();
//	untried_actions.erase(untried_actions.begin());
//	TwixtGame next_state = state.getNextState(action);
//	MonteCarloTreeSearchNode* child_node = new MonteCarloTreeSearchNode(next_state, this, action);
//	children.push_back(child_node);
//	return child_node;
//}
//
//bool MonteCarloTreeSearchNode::is_terminal_node()
//{
//	return state.isGameOver();
//}
//
//int MonteCarloTreeSearchNode::rollout()
//{
//	TwixtGame current_rollout_state = state;
//	while (!current_rollout_state.isGameOver())
//	{
//		ActionSet valid_actions = current_rollout_state.getValidActions();
//		if (valid_actions.empty())
//		{
//			break;
//		}
//		std::uniform_int_distribution<> distr(0, valid_actions.size() - 1);
//		int random_index = distr(eng);
//		Action random_action = *std::next(valid_actions.begin(), random_index);
//		current_rollout_state = current_rollout_state.getNextState(random_action);
//	}
//	return current_rollout_state.gameResult();
//}
//
//void MonteCarloTreeSearchNode::backpropagate(int result)
//{
//	visits++;
//	if (result == 1)
//	{
//		wins++;
//	}
//	else if (result == -1)
//	{
//		losses++;
//	}
//	if (parent != nullptr)
//	{
//		parent->backpropagate(result);
//	}
//}
//
//bool MonteCarloTreeSearchNode::is_fully_expanded()
//{
//	return untried_actions.empty();
//}
//
//MonteCarloTreeSearchNode* MonteCarloTreeSearchNode::best_child(double c_param)
//{
//	MonteCarloTreeSearchNode* best_child = nullptr;
//	double best_score = -std::numeric_limits<double>::infinity();
//	for (MonteCarloTreeSearchNode* child : children)
//	{
//		double exploit = (double)wins_minus_loses() / child->visits;
//		double explore = sqrt(2.0 * log(visits) / child->visits);
//		double score = exploit + c_param * explore;
//		if (score > best_score)
//		{
//			best_score = score;
//			best_child = child;
//		}
//	}
//	return best_child;
//}
//
//MonteCarloTreeSearchNode* MonteCarloTreeSearchNode::_tree_policy()
//{
//	MonteCarloTreeSearchNode* current_node = this;
//	while (!current_node->is_terminal_node())
//	{
//		if (!current_node->is_fully_expanded())
//		{
//			return current_node->expand();
//		}
//		else
//		{
//			current_node = current_node->best_child(1.0);
//		}
//	}
//	return current_node;
//}
//
//Action MonteCarloTreeSearchNode::get_best_action()
//{
//	int simulation_no = 100;
//	for (int i = 0; i < simulation_no; i++)
//	{
//		MonteCarloTreeSearchNode* promising_node = _tree_policy();
//		int reward = promising_node->rollout();
//		promising_node->backpropagate(reward);
//	}
//	return best_child(0.0)->parent_action;
//}
