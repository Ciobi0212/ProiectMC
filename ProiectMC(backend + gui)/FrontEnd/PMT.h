//Pure Monte Carlo
#include "TwixtGame.h"

class PMT { 
public:
	PMT();
	~PMT();
	Action<> getBestAction(TwixtGame& game, size_t numSimulations);
};