#ifndef __PERMUTATION_ACTION_H_
#define __PERMUTATION_ACTION_H_

#include "permutation.h"
#include "puzzleaction.h"

class PermutationAction : public PuzzleAction
{
public:
	PermutationAction();

	void setPermutation(const Permutation &permutation);
	PuzzleAction *cloneAction();
	void execute(PuzzleData *puzzleData, bool inverted);
private:
	void reportError(const string &message);
	
	Permutation m_permutation;
};

#endif
