#include "puzzleactionstorage.h"

PuzzleActionStorage::PuzzleActionStorage()
	:m_puzzleActionMap()
{
}

void PuzzleActionStorage::addPuzzleAction(const string &actionName, PuzzleAction *puzzleAction)
{
	m_puzzleActionMap[actionName] = puzzleAction;
}

PuzzleAction *PuzzleActionStorage::getActionByName(const string &actionName)
{
	if (m_puzzleActionMap.find(actionName) == m_puzzleActionMap.end())
		return NULL;

	return m_puzzleActionMap[actionName];
}

PuzzleAction *PuzzleActionStorage::getRandomAction()
{
	vector<pair<string, PuzzleAction *>> entrySet(m_puzzleActionMap.begin(), m_puzzleActionMap.end());
	int randomIndex = rand() % entrySet.size();
	return entrySet[randomIndex].second;
}
