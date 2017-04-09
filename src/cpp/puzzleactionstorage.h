#ifndef __PUZZLE_ACTION_STORAGE_H_
#define __PUZZLE_ACTION_STORAGE_H_

#include "common.h"
#include "puzzleaction.h"

class PuzzleActionStorage
{
public:
	PuzzleActionStorage();

	void addPuzzleAction(const string &actionName, PuzzleAction *puzzleAction);
	PuzzleAction *getActionByName(const string &actionName);
	PuzzleAction *getRandomAction();
private:
	map<string, PuzzleAction *> m_puzzleActionMap;
};

#endif
