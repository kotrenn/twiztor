#ifndef __PUZZLE_CONTROLLER_H_
#define __PUZZLE_CONTROLLER_H_

#include "actionqueue.h"
#include "keylistener.h"
#include "puzzleactionstorage.h"
#include "puzzledata.h"

class PuzzleController : public KeyListener
{
public:
	PuzzleController(PuzzleData *puzzleData);
	virtual ~PuzzleController();

	void setPuzzleData(PuzzleData *puzzleData) { m_puzzleData = puzzleData; }

	void activatePermutation(unsigned int index);
	void activatePermutation(unsigned int index, bool inverted);
	void solve();
	void randomize();

	// TODO: PuzzleController: Macro system
	void saveMacro() {}
	void addMacro() {}

	void eventKeyUp(const SDL_KeyboardEvent &key);
	
private:
	PuzzleData *m_puzzleData;
	PuzzleActionStorage *m_puzzleActionStorage;
	ActionQueue *m_actionQueue;
};

#endif
