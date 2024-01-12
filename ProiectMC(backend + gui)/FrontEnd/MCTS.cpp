#include "MCTS.h"
#include <fstream>

MonteCarloTreeSearchNode::MonteCarloTreeSearchNode(TwixtGame& state, std::mt19937& eng, MonteCarloTreeSearchNode* parent, Action parent_action) : eng{ eng }, parent{ parent }, parent_action{ parent_action }, wins{ 0.0 }, visits{ 0 }, playerTurn{ state.getCurrentPlayer().getColor() }, untried_actions{ state.getValidPegActions() }
{}

MonteCarloTreeSearchNode::~MonteCarloTreeSearchNode() = default;

MonteCarloTreeSearchNode* MonteCarloTreeSearchNode::select(TwixtGame& state) const
{
	double bestUcb = -std::numeric_limits<double>::infinity();
	std::vector<MonteCarloTreeSearchNode*> bestChildren;
	for (const auto& child : children)
	{
		if (child->visits == 0)
		{
			bestChildren.push_back(child);
			break;
		}
		else {
			double ucb = getUCBValue(child, 2.0);
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

	ActionSet nextLinkActions = state.getValidLinkActionsImproved(std::get<1>(action));
	for (auto linkAction : nextLinkActions) {
		 state.goToNextState(linkAction);
	}
	state.switchPlayer();
	MonteCarloTreeSearchNode* child_node = new MonteCarloTreeSearchNode(state,eng, this, action);
	children.push_back(child_node);
	return child_node;
}

double MonteCarloTreeSearchNode::rollout(TwixtGame& state) const
{
	TwixtGame gameCopy(state);
	Player player = gameCopy.getCurrentPlayer();
	ActionSet nextPegMoves = gameCopy.getValidPegActions();
	ActionSet nextLinkActions = gameCopy.getValidLinkActions();
	std::vector<Action> simulationMoves;

	if (gameCopy.getCurrentPlayer().checkForWin(gameCopy.getBoard())) {
		return gameCopy.getCurrentPlayer().getColor() == player.getColor() ? -1 : 1;
	}


	while (true) {
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
		return gameCopy.getCurrentPlayer().getColor() == player.getColor() ? -1 : 1;
	}
	
	
	return 0.5;
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


double MonteCarloTreeSearchNode::getUCBValue(MonteCarloTreeSearchNode* node, double exploration_parameter) const
{
	double ucb_value = (double)node->wins / (double)node->visits + exploration_parameter * sqrt(log(node->parent->visits) / (double)node->visits);
	return ucb_value;
}

bool MonteCarloTreeSearchNode::is_terminal_node() const
{
	return untried_actions.empty() && children.size() > 0;
}

MCTS::MCTS(TwixtGame& state) : eng{ rd() }, original_state{ state }
{
	this->root = new MonteCarloTreeSearchNode(state, eng);
}

MCTS::~MCTS()
{
	dealocateTree(root);
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
		TwixtGame state_copy{ original_state };
	
		while (node->is_terminal_node())
		{
			node = node->select(state_copy);
		}
		
		node = node->expand(state_copy);
		double reward = node->rollout(state_copy);
		node->backpropagate(reward);
	}
	double bestUCB = 0;
	double bestWinRate = -std::numeric_limits<double>::infinity();
	MonteCarloTreeSearchNode* bestChild = nullptr;
	
	for (uint16_t i = 0; i < root->children.size()-1; i++) {
		MonteCarloTreeSearchNode* child = root->children[i];
		double winRate = (double)child->wins / (double)child->visits;
		if (winRate > bestWinRate) {
			bestWinRate = winRate;
			bestChild = child;
		}
	}
	
	return bestChild->parent_action;
}
