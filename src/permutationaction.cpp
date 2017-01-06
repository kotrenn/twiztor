#include "permutationaction.h"

#include "common.h"

PermutationAction::PermutationAction()
	:m_permutation()
{
}

void PermutationAction::setPermutation(const Permutation &permutation)
{
	m_permutation = permutation;
}

PuzzleAction *PermutationAction::cloneAction()
{
	PermutationAction *clonedAction = new PermutationAction();
	clonedAction->m_permutation = m_permutation;
	return clonedAction;
}

void PermutationAction::execute(PuzzleData *puzzleData, bool inverted)
{
	// TODO: PermutationAction::execute()
	//if (m_permutation == null)
	//	reportError("No Permutation applied to BasicAction");
	//else
		m_permutation.apply(puzzleData, inverted);
}

void PermutationAction::reportError(const string &message)
{
	cout << "PermutationAction error: " << message << endl;
}
