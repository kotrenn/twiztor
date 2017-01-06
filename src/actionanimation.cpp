#include "actionanimation.h"

#include <SDL2/SDL.h>

ActionAnimation::ActionAnimation(PuzzleAction *puzzleAction)
	:m_puzzleAction(puzzleAction),
	 m_startTime(SDL_GetTicks()),
	 m_durationTime(1200)
{
}

float ActionAnimation::getTime() const
{
	Uint32 currentTime = SDL_GetTicks();
	Uint32 delta = currentTime - m_startTime;
	float ret = (float)delta / (float)m_durationTime;
	if (ret > 1.0) ret = 1.0;
	return ret;
}
