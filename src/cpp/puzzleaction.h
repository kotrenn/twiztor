#ifndef __PUZZLE_ACTION_H_
#define __PUZZLE_ACTION_H_

#include "puzzledata.h"

class PuzzleAction
{
public:
	virtual PuzzleAction *cloneAction() = 0;
	virtual void execute(PuzzleData *puzzleData, bool inverted) = 0;
};

#endif
