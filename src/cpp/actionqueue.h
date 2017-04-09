#ifndef __ACTION_QUEUE_H_
#define __ACTION_QUEUE_H_

#include "common.h"
#include "puzzleaction.h"

class ActionQueue
{
public:
	ActionQueue();

	void add(PuzzleAction *puzzleAction);

private:
	list<PuzzleAction *> m_actionList;
};

#endif
