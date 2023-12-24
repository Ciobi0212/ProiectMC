#include "PMT.h"
#include <unordered_map>
#include <random>
#include <fstream>

PMT::PMT() = default;

PMT::~PMT() = default;

Action PMT::getBestAction(TwixtGame& game, size_t numSimulations)
{
	std::unordered_map<Action, double, ActionHash> evaluations;
	ActionSet validActions = game.getValidActions();
	std::random_device rd;
	std::mt19937 eng(rd());
	
	for (size_t generation = 0; generation < numSimulations; ++generation)
	{
		TwixtGame gameCopy(game);
		Player player = gameCopy.getCurrentPlayer();
		ActionSet nextPegMoves = gameCopy.getValidPegActions();
		ActionSet nextLinkActions = gameCopy.getValidLinkActions();
		std::vector<Action> simulationMoves;
		double score = 10000.0;
		
		while (!nextPegMoves.empty() || !nextLinkActions.empty()) {
			Action randomMove;
			nextPegMoves = gameCopy.getValidPegActions();
			

			 if (!nextPegMoves.empty()) {
				std::uniform_int_distribution<> distr(0, nextPegMoves.size() - 1);
				int randomIndexPeg = distr(eng);
				auto it = nextPegMoves.begin();
				std::advance(it, randomIndexPeg);
				randomMove = *it;
				if (randomMove == Action(ActionType::PLACE_PEG, Position(6,2), Position(6,2)))
					int a = 2;
					
				simulationMoves.push_back(randomMove);
				gameCopy = gameCopy.getNextState(randomMove);
				}
			 nextLinkActions = gameCopy.getValidLinkActions();
			 if (!nextLinkActions.empty()) {
				 for (auto linkAction : nextLinkActions) {
					simulationMoves.push_back(linkAction);
					gameCopy = gameCopy.getNextState(linkAction);
				 }
			 }
			
			if (player.checkForWin(gameCopy.getBoard()) || (gameCopy.isDraw())) {
				break;
			}
			gameCopy.switchPlayer();
			player = gameCopy.getCurrentPlayer();
			score--;
		}
		if (player.getColor() == game.getCurrentPlayer().getColor() && player.checkForWin(gameCopy.getBoard())) {
			//put in evaluations the latest move from simulationMoves that is in validActions
			for (int index = simulationMoves.size() - 1; index >= 0; --index) {
				if (validActions.find(simulationMoves[index]) != validActions.end() && std::get<0>(simulationMoves[index]) == ActionType::PLACE_PEG) {
					if (simulationMoves[index] == Action(ActionType::PLACE_PEG, Position(6, 2), Position(6, 2)))
						int a = 2;
					double reward = (double)((score / simulationMoves.size()) - index);
					evaluations[simulationMoves[index]] += reward;
				}
			}
		}
		else if (player.getColor() != game.getCurrentPlayer().getColor() && player.checkForWin(gameCopy.getBoard())) {
			for (int index = simulationMoves.size() - 1; index >= 0; --index) {
				if (validActions.find(simulationMoves[index]) != validActions.end() && std::get<0>(simulationMoves[index]) == ActionType::PLACE_PEG) {
					if (simulationMoves[index] == Action(ActionType::PLACE_PEG, Position(6, 2), Position(6, 2)))
						int a = 2;
					double reward = (double)((score / simulationMoves.size()) - index) / 2.0;
					evaluations[simulationMoves[index]] -= reward;
					
					
				}
			}
		}
		else {
			//put in evaluations the latest move from simulationMoves that is in validActions
			for (int index = simulationMoves.size() - 1; index >= 0; --index) {
				if (validActions.find(simulationMoves[index]) != validActions.end() && std::get<0>(simulationMoves[index]) == ActionType::PLACE_PEG) {
					if (simulationMoves[index] == Action(ActionType::PLACE_PEG, Position(6, 2), Position(6, 2)))
						int a = 2;
					double reward = (double)((score / simulationMoves.size()) - index) / 2.0;
					evaluations[simulationMoves[index]] += reward;
				}
			}
		}
	}
	
	Action bestMove;
	std::ofstream file;

	file.open("bestAction.txt");
	long long bestScore = std::numeric_limits<long long>::min();
	for (auto& pair : evaluations) {
		if (pair.second > bestScore) {
			bestMove = pair.first;
			bestScore = pair.second;
		}
		//write every evaluation to a file
		if (std::get<0>(pair.first) == ActionType::PLACE_PEG)
			file << "PLACE_PEG" << std::endl;
		else if (std::get<0>(pair.first) == ActionType::PLACE_LINK)
			file << "PLACE_LINK" << std::endl;
			
		
		file << static_cast<int>(std::get<0>(pair.first)) << std::endl;
		file << std::get<1>(pair.first).first << " " << std::get<1>(pair.first).second << std::endl;
		file << std::get<2>(pair.first).first << " " << std::get<2>(pair.first).second<<std::endl;
		file << "score: " << pair.second<<std::endl;
	}
	//write best move to a file
	file << "best move: " << std::endl;
	if (std::get<0>(bestMove) == ActionType::PLACE_PEG)
		file << "PLACE_PEG" << std::endl;
	else if (std::get<0>(bestMove) == ActionType::PLACE_LINK)
		file << "PLACE_LINK" << std::endl;
	
	file << static_cast<int>(std::get<0>(bestMove)) << std::endl;
	file << std::get<1>(bestMove).first << " " << std::get<1>(bestMove).second << std::endl;
	file << std::get<2>(bestMove).first << " " << std::get<2>(bestMove).second << std::endl;
	
	file.close();
	return bestMove;
}
