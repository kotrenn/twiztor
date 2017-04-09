#include "actionqueue.h"

ActionQueue::ActionQueue()
	:m_actionList()
{
}

void ActionQueue::add(PuzzleAction *puzzleAction)
{
	m_actionList.push_back(puzzleAction);
}
