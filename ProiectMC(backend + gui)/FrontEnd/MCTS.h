#pragma once

#include "TwixtGame.h"
#include <memory>
#include <random>
#include <thread>

using namespace twixt;

class MonteCarloTreeSearchNode : public std::enable_shared_from_this<MonteCarloTreeSearchNode> {
public:
    // Constructors and destructor
    MonteCarloTreeSearchNode(TwixtGame& state, std::mt19937& eng, std::shared_ptr<MonteCarloTreeSearchNode> parent = nullptr, Action parent_action = Action(ActionType::NONE, { -1,-1 }, { -1, -1 }));
    ~MonteCarloTreeSearchNode();

    // Tree operations
    std::shared_ptr<MonteCarloTreeSearchNode> select(TwixtGame& state) const;
    std::shared_ptr<MonteCarloTreeSearchNode> expand(TwixtGame& state);
    double rollout(TwixtGame& state) const;
    void backpropagate(double result);
    double getUCBValue(std::shared_ptr<MonteCarloTreeSearchNode> node, double exploration_parameter = 1.414) const;
    bool is_terminal_node() const;

    // Member variables
    std::shared_ptr<MonteCarloTreeSearchNode> parent;
    Color playerTurn;
    Action parent_action;
    std::vector<std::shared_ptr<MonteCarloTreeSearchNode>> children;
    ActionSet untried_actions;
    double wins;
    double visits;
    std::mt19937& eng;
};

class MCTS {
public:
    // Constructors and destructor
    MCTS(TwixtGame& state);
    ~MCTS();

    // Tree operations
    void deallocateTree(std::shared_ptr<MonteCarloTreeSearchNode> node);
    std::vector<Action> best_actions(uint32_t simulations_number);

private:
    // Member variables
    std::shared_ptr<MonteCarloTreeSearchNode> root;
    TwixtGame original_state;
    std::random_device rd;
    std::mt19937 eng;
};
