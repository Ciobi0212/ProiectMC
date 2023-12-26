#include "MCTS.h"
#include <fstream>
//#include "MCTS.h"
//
MonteCarloTreeSearchNode::MonteCarloTreeSearchNode(TwixtGame& state, MonteCarloTreeSearchNode* parent, Action parent_action)
{
	this->parent = parent;
	this->parent_action = parent_action;
	this->wins = 0.0;
	this->visits = 0;
	this->playerTurn = state.getCurrentPlayer().getColor();
	this->untried_actions = state.getValidPegActions();
}

MonteCarloTreeSearchNode::~MonteCarloTreeSearchNode() = default;
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

MonteCarloTreeSearchNode* MonteCarloTreeSearchNode::select(TwixtGame& state)
{
	double bestUcb = -std::numeric_limits<double>::infinity();
	std::vector<MonteCarloTreeSearchNode*> bestChildren;
	for (const auto& child : children)
	{
		if (child->visits == 0)
		{
			return child;
		}
		else {
			double ucb = getUCBValue(child, sqrt(2.0));
			if (ucb > bestUcb)
			{
				bestUcb = ucb;
				bestChildren.clear();
			}
			if (ucb == bestUcb)
			{
				bestChildren.push_back(child);
			}
		}
	}

	
	std::uniform_int_distribution<> distr(0, bestChildren.size() - 1);
	int random_index = distr(eng);
	state.goToNextState(bestChildren[random_index]->parent_action);
	ActionSet nextLinkActions = state.getValidLinkActionsImproved(std::get<1>(bestChildren[random_index]->parent_action));
	for (auto linkAction : nextLinkActions) {
		state.goToNextState(linkAction);
	}
	state.switchPlayer();
	return bestChildren[random_index];
}

MonteCarloTreeSearchNode* MonteCarloTreeSearchNode::expand(TwixtGame& state)
{
	//pick a random untried_action
	std::uniform_int_distribution<> distr(0, untried_actions.size() - 1);
	int random_index = distr(eng);
	Action action = *std::next(untried_actions.begin(), random_index);
	untried_actions.erase(action);
	
	
	state.goToNextState(action);
	if (std::get<1>(action) == Position(1, 9))
		int a = 2;
	ActionSet nextLinkActions = state.getValidLinkActionsImproved(std::get<1>(action));
	for (auto linkAction : nextLinkActions) {
		 state.goToNextState(linkAction);
	}
	state.switchPlayer();
	MonteCarloTreeSearchNode* child_node = new MonteCarloTreeSearchNode(state, this, action);
	children.push_back(child_node);
	return child_node;
}

double MonteCarloTreeSearchNode::rollout(TwixtGame& state)
{
	TwixtGame gameCopy(state);
	Player player = gameCopy.getCurrentPlayer();
	ActionSet nextPegMoves = gameCopy.getValidPegActions();
	ActionSet nextLinkActions = gameCopy.getValidLinkActionsImproved(std::get<1>(parent_action));
	std::vector<Action> simulationMoves;

	if (gameCopy.getCurrentPlayer().checkForWin(gameCopy.getBoard())) {
		if (gameCopy.getCurrentPlayer().getColor() == player.getColor()) {
			return -1;
		}
		else {
			return 1;
		}
	}


	while (!nextPegMoves.empty() || !nextLinkActions.empty()) {
		Action randomMove;
		nextPegMoves = gameCopy.getValidPegActions();


		if (!nextPegMoves.empty()) {
			std::uniform_int_distribution<> distr(0, nextPegMoves.size() - 1);
			int randomIndexPeg = distr(eng);
			auto it = nextPegMoves.begin();
			std::advance(it, randomIndexPeg);
			randomMove = *it;
			simulationMoves.push_back(randomMove);
			 gameCopy.goToNextState(randomMove);
			 if (std::get<1>(randomMove) == Position(1, 9))
				 int a = 2;
		}
		nextLinkActions = gameCopy.getValidLinkActionsImproved(std::get<1>(randomMove));
		if (!nextLinkActions.empty()) {
			for (auto linkAction : nextLinkActions) {
				simulationMoves.push_back(linkAction);
				 gameCopy.goToNextState(linkAction);
			}
		}

		if (gameCopy.getCurrentPlayer().checkForWin(gameCopy.getBoard()) || (gameCopy.isDraw())) {
			break;
		}
		gameCopy.switchPlayer();
	}
	if (gameCopy.getCurrentPlayer().checkForWin(gameCopy.getBoard())) {
		if (gameCopy.getCurrentPlayer().getColor() == player.getColor()) {
			return -1;
		}
		else {
			return 1;
		}
	}
	
	else {
		return 0.5;
	}
}

void MonteCarloTreeSearchNode::backpropagate(double result)
{
	MonteCarloTreeSearchNode* current_node = this;
	while (current_node != nullptr)
	{
		current_node->visits++;
		current_node->wins += result;
		result = -result;
		current_node = current_node->parent;
	}
}


double MonteCarloTreeSearchNode::getUCBValue(MonteCarloTreeSearchNode* node, double exploration_parameter)
{
	double ucb_value = (double)node->wins / (double)node->visits + exploration_parameter * sqrt(log(node->parent->visits) / (double)node->visits);
	return ucb_value;
}

bool MonteCarloTreeSearchNode::is_terminal_node()
{
	return untried_actions.empty() && children.size() > 0;
}

MCTS::MCTS(TwixtGame& state)
{
	this->root = new MonteCarloTreeSearchNode(state);
	original_state = state;
}

MCTS::~MCTS()
{
	//delete the whole tree
}

void MCTS::dealocateTree(MonteCarloTreeSearchNode* node)
{
	if (node == nullptr)
		return;
	for (auto child : node->children)
	{
		dealocateTree(child);
	}
	delete node;
}

Action MCTS::best_action(uint16_t simulations_number)
{
	for (uint16_t i = 0; i < simulations_number; i++) {
		MonteCarloTreeSearchNode* node = root;
		TwixtGame state_copy = original_state;
		if (i == 2000)
			int a = 2;
		while (node->is_terminal_node())
		{
			node = node->select(state_copy);
		}
		if (std::get<1>(node->parent_action) == Position(1, 9))
			int a = 2;
		node = node->expand(state_copy);
		double reward = node->rollout(state_copy);
		node->backpropagate(reward);
	}
	double bestUCB = 0;
	double bestWinRate = -std::numeric_limits<double>::infinity();
	MonteCarloTreeSearchNode* bestChild = nullptr;
	std::ofstream file;
	file.open("bestMove.txt");
	//get best child with highest win rate
	for (int i = 0; i < root->children.size()-1; i++) {
		MonteCarloTreeSearchNode* child = root->children[i];
		double winRate = (double)child->wins / (double)child->visits;
		/*if (child->visits > mostVisits) {
			mostVisits = child->visits;
			bestChild = child;
		}*/
		if (winRate > bestWinRate) {
			bestWinRate = winRate;
			bestChild = child;
			file << std::endl;
			Action bestMove = bestChild->parent_action;
			if (std::get<0>(bestMove) == ActionType::PLACE_PEG)
				file << "PLACE_PEG" << std::endl;
			else if (std::get<0>(bestMove) == ActionType::PLACE_LINK)
				file << "PLACE_LINK" << std::endl;

			file << static_cast<int>(std::get<0>(bestMove)) << std::endl;
			file << std::get<1>(bestMove).first << " " << std::get<1>(bestMove).second << std::endl;
			file << std::get<2>(bestMove).first << " " << std::get<2>(bestMove).second << std::endl;
			file << bestChild->visits << std::endl;
			file << bestChild->wins << std::endl;
		}
	}
	//write best move to fi
	file << "BEST MOVE:" << std::endl;
	Action bestMove = bestChild->parent_action;
	if (std::get<0>(bestMove) == ActionType::PLACE_PEG)
		file << "PLACE_PEG" << std::endl;
	else if (std::get<0>(bestMove) == ActionType::PLACE_LINK)
		file << "PLACE_LINK" << std::endl;

	file << static_cast<int>(std::get<0>(bestMove)) << std::endl;
	file << std::get<1>(bestMove).first << " " << std::get<1>(bestMove).second << std::endl;
	file << std::get<2>(bestMove).first << " " << std::get<2>(bestMove).second << std::endl;
	file << bestChild->visits << std::endl;
	file << bestChild->wins << std::endl;

	file.close();
	
	return bestChild->parent_action;
}
