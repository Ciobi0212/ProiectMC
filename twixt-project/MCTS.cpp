#include "MCTS.h"
#include <fstream>
#include <ranges>

MCTSNode::MCTSNode(TwixtGame& state, std::mt19937& eng, std::shared_ptr<MCTSNode> parent,Action<> parent_action)
    : eng{ eng }, parent{ parent }, parent_action{ parent_action }, wins{ 0.0 }, visits{ 0 }, playerTurn{ state.getCurrentPlayer().getColor() }, untried_actions{ state.getCurrentPlayer().getValidPegPositions() }
{}

MCTSNode::~MCTSNode() = default;

std::shared_ptr<MCTSNode> MCTSNode::select(TwixtGame& state) const {
    double bestUcb = -std::numeric_limits<double>::infinity();
    std::vector<std::shared_ptr<MCTSNode>> bestChildren;

    for (const auto& child : children) {
        if (child->visits == 0) {
            bestChildren.push_back(child);
            break;
        }
        else {
            double ucb = getUCBValue(child, sqrt(2.0));
            if (ucb > bestUcb) {
                bestUcb = ucb;
                bestChildren.clear();
            }
            if (ucb == bestUcb) {
                bestChildren.push_back(child);
            }
        }
    }

    size_t random_index = randomIndex(bestChildren.size(), eng);
    state.goToNextState(bestChildren[random_index]->parent_action);
    ActionSet<> nextLinkActions = state.getValidLinkActionsImproved(std::get<1>(bestChildren[random_index]->parent_action));

    std::for_each(nextLinkActions.begin(), nextLinkActions.end(), [&state](const auto& linkAction) { state.goToNextState(linkAction); });

    state.switchPlayer();
    return bestChildren[random_index];
}

std::shared_ptr<MCTSNode> MCTSNode::expand(TwixtGame& state) {
   Action<> action = extractRandomAction(untried_actions, eng);

    state.goToNextState(action);

    ActionSet nextLinkActions = state.getValidLinkActionsImproved(std::get<1>(action));

    std::for_each(nextLinkActions.begin(), nextLinkActions.end(), [&state](const auto& linkAction) { state.goToNextState(linkAction); });

    state.switchPlayer();
    auto child_node = std::make_shared<MCTSNode>(state, eng, shared_from_this(), action);
    children.push_back(child_node);
    return child_node;
}

double MCTSNode::rollout(TwixtGame& state) const {
    TwixtGame gameCopy(state);
    Player player = gameCopy.getCurrentPlayer();
    ActionSet<> nextPegMoves = gameCopy.getCurrentPlayer().getValidPegPositions();
    ActionSet<> nextLinkActions;

    if (gameCopy.getCurrentPlayer().checkForWin(gameCopy.getBoard())) {
        return gameCopy.getCurrentPlayer().getColor() == player.getColor() ? -1 : 1;
    }

    while (!nextPegMoves.empty()) {
       Action<> randomMove;
        nextPegMoves = gameCopy.getCurrentPlayer().getValidPegPositions();

        if (!nextPegMoves.empty()) {
            std::uniform_int_distribution<> distr(0, nextPegMoves.size() - 1);
            int randomIndexPeg = distr(eng);
            auto it = nextPegMoves.begin();
            std::advance(it, randomIndexPeg);
            randomMove = *it;
            gameCopy.goToNextState(randomMove);
        }

        nextLinkActions = gameCopy.getValidLinkActionsImproved(std::get<1>(randomMove));

        if (!nextLinkActions.empty()) {
            for (const auto& linkAction : nextLinkActions) {
                gameCopy.goToNextState(linkAction);
            }
        }

        if (gameCopy.getCurrentPlayer().checkForWin(gameCopy.getBoard())) {
            break;
        }

        gameCopy.switchPlayer();
    }

    if (gameCopy.getCurrentPlayer().checkForWin(gameCopy.getBoard())) {
        return gameCopy.getCurrentPlayer().getColor() == player.getColor() ? -1 : 1;
    }

    return 0.5;
}

void MCTSNode::backpropagate(double result) {
    std::shared_ptr<MCTSNode> current_node = shared_from_this();

    while (current_node) {
        current_node->visits++;
        current_node->wins += result;
        result = -result;
        current_node = current_node->parent;
    }
}

double MCTSNode::getUCBValue(std::shared_ptr<MCTSNode> node, double exploration_parameter) const {
    double ucb_value = static_cast<double>(node->wins) / static_cast<double>(node->visits) + exploration_parameter * sqrt(log(node->parent->visits) / static_cast<double>(node->visits));
    return ucb_value;
}

bool MCTSNode::is_terminal_node() const {
    return untried_actions.empty() && !children.empty();
}

MCTS::MCTS(TwixtGame& state) : eng{ rd() }, original_state{ state }, root{ std::make_shared<MCTSNode>(state, eng) } {}

MCTS::~MCTS() {
	deallocateTree(root);
}

void MCTS::deallocateTree(std::shared_ptr<MCTSNode> node) {
	if (node->children.empty()) {
		return;
	}

	for (const auto& child : node->children) {
		deallocateTree(child);
	}

	node->children.clear();
}

std::vector<Action<>> MCTS::best_actions(uint32_t simulations_number) {
    for (uint32_t i = 0; i < simulations_number; i++) {
        std::shared_ptr<MCTSNode> node = root;
        TwixtGame state_copy{ original_state };

        while (node->is_terminal_node()) {
            node = node->select(state_copy);
        }

        node = node->expand(state_copy);
        double reward = node->rollout(state_copy);
        node->backpropagate(reward);
    }

    double bestUCB = 0;
    double bestWinRate = -std::numeric_limits<double>::infinity();
    uint32_t bestVisitCount = 0;
    std::vector<Action<>> bestActions;

    std::ofstream fout("moves");

    for (uint32_t i = 0; i < root->children.size(); i++) {
        std::shared_ptr<MCTSNode> child = root->children[i];
        double winRate = static_cast<double>(child->wins) / static_cast<double>(child->visits);

        if (winRate > bestWinRate) {
            bestActions.push_back(child->parent_action);
            bestWinRate = winRate;
            fout << "Move " << std::get<1>(child->parent_action).first << " " << std::get<1>(child->parent_action).second << "\n";
            fout << "Wins: " << child->wins << "\n";
            fout << "Visits: " << child->visits << "\n";
            fout << "Win rate: " << winRate << "\n";
        }
    }

    fout.close();
    return bestActions;
}
