#ifndef __ACTION_ANIMATION_H_
#define __ACTION_ANIMATION_H_

#include "puzzleaction.h"

class ActionAnimation
{
public:
	ActionAnimation(PuzzleAction *puzzleAction);

	float getTime() const;
private:
	PuzzleAction *m_puzzleAction;
	Uint32 m_startTime;
	Uint32 m_durationTime;
};

#endif
