#ifndef __PUZZLE_RENDERER_H_
#define __PUZZLE_RENDERER_H_

#include "puzzledata.h"

class PuzzleData;

class PuzzleRenderer
{
public:
	PuzzleRenderer();

	void render(const PuzzleData &puzzleData) const;
private:
};

#endif
